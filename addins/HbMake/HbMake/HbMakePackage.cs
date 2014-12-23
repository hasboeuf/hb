using System;
using System.Diagnostics;
using System.Globalization;
using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.ComponentModel.Design;
using Microsoft.Win32;
using Microsoft.VisualStudio;
using Microsoft.VisualStudio.Shell.Interop;
using Microsoft.VisualStudio.OLE.Interop;
using Microsoft.VisualStudio.Shell;

using EnvDTE;
using EnvDTE80;

namespace hb
{
    /// <summary>
    /// This is the class that implements the package exposed by this assembly.
    ///
    /// The minimum requirement for a class to be considered a valid package for Visual Studio
    /// is to implement the IVsPackage interface and register itself with the shell.
    /// This package uses the helper classes defined inside the Managed Package Framework (MPF)
    /// to do it: it derives from the Package class that provides the implementation of the 
    /// IVsPackage interface and uses the registration attributes defined in the framework to 
    /// register itself and its components with the shell.
    /// </summary>
    // This attribute tells the PkgDef creation utility (CreatePkgDef.exe) that this class is
    // a package.
    [PackageRegistration(UseManagedResourcesOnly = true)]
    // This attribute is used to register the information needed to show this package
    // in the Help/About dialog of Visual Studio.
    [InstalledProductRegistration("#110", "#112", "1.0", IconResourceID = 400)]
    // This attribute is needed to let the shell know that this package exposes some menus.
    [ProvideMenuResource("Menus.ctmenu", 1)]
    [Guid(GuidList.guidHbMakePkgString)]

    // Loads when solution is fully loaded.
    [ProvideAutoLoad(VSConstants.UICONTEXT.SolutionExistsAndFullyLoaded_string)]
    public sealed class HbMakePackage : Package
    {

        #region Attributes
        QtSolution mQtSolution;
        private SolutionEvents mSolutionEvents;
        #endregion

        /// <summary>
        /// Default constructor of the package.
        /// Inside this method you can place any initialization code that does not require 
        /// any Visual Studio service because at this point the package object is created but 
        /// not sited yet inside Visual Studio environment. The place to do all the other 
        /// initialization is the Initialize method.
        /// </summary>
        public HbMakePackage()
        {
            Debug.WriteLine(string.Format(CultureInfo.CurrentCulture, "Entering constructor for: {0}", this.ToString()));

            mQtSolution = null;
        }


        /////////////////////////////////////////////////////////////////////////////
        // Overridden Package Implementation
        #region Package Members

        /// <summary>
        /// Initialization of the package; this method is called right after the package is sited, so this is the place
        /// where you can put all the initialization code that rely on services provided by VisualStudio.
        /// </summary>
        protected override void Initialize()
        {
            Debug.WriteLine (string.Format(CultureInfo.CurrentCulture, "Entering Initialize() of: {0}", this.ToString()));
            base.Initialize();

            DTE2 dte = GetService(typeof(DTE)) as DTE2;
            mSolutionEvents = dte.Events.SolutionEvents;
            mSolutionEvents.Opened += OnSolutionOpened;
            mSolutionEvents.Renamed += OnSolutionRenamed;

            Services.Instance.Init(dte);

            // Add our command handlers for menu (commands must exist in the .vsct file)
            OleMenuCommandService mcs = GetService(typeof(IMenuCommandService)) as OleMenuCommandService;
            if ( null != mcs )
            {
                // Create the command for the menu item.
                CommandID menuCommandID = new CommandID(GuidList.guidHbMakeCmdSet, (int)PkgCmdIDList.CommandIdExecuteQMake);
                MenuCommand menuItem = new MenuCommand(MenuItemCallback, menuCommandID );
                mcs.AddCommand( menuItem );
            }

            OutputPane logger = Services.Instance.Logger;
            logger.OpenOutputPane();
            logger.WriteOutputPane("HbMake initialized!");

            if(dte.Solution.IsOpen && !String.IsNullOrEmpty(dte.Solution.FullName)) // If the solution is already loaded.
            {
                OnSolutionOpened();
            }
        }
        #endregion

        /// <summary>
        /// This function is the callback used to execute a command when the a menu item is clicked.
        /// See the Initialize method to see how the menu item is associated to this function using
        /// the OleMenuCommandService service and the MenuCommand class.
        /// </summary>
        private void MenuItemCallback(object sender, EventArgs e)
        {

            uint command_id = 0;

            MenuCommand menuCommand = sender as MenuCommand;
            if (null != menuCommand)
            {
                command_id = (uint)menuCommand.CommandID.ID;
            }

            OutputPane logger = Services.Instance.Logger;
            logger.ShowOutputPane();
            bool command_ok = true;

            switch (command_id)
            {
                case PkgCmdIDList.CommandIdExecuteQMake:
                    logger.WriteOutputPane("QMake request...");
                    break;

                case PkgCmdIDList.CommandId2:
                    logger.WriteOutputPane("Command2 request...");
                    command_ok = false;
                    break;

                case PkgCmdIDList.CommandId3:
                    logger.WriteOutputPane("Command3 request...");
                    command_ok = false;
                    break;

                case PkgCmdIDList.CommandId4:
                    logger.WriteOutputPane("Command4 request...");
                    command_ok = false;
                    break;

                default:
                    logger.WriteOutputPane("Unknow command !");
                    command_ok = false;
                    break;
            }

            if(!command_ok)
            {
                return;
            }

            ICollection items = GetSelectedItems();

            foreach (VSITEMSELECTION item in items)
            {
                if (items.Count == 1 && item.pHier == null)
                {
                    switch (command_id)
                    {
                        case PkgCmdIDList.CommandIdExecuteQMake:
                            logger.WriteOutputPane("Updating solution...");
                            mQtSolution.UpdateSolution();
                            logger.WriteOutputPane("Solution updated !");
                            break;
                    }
                }
                else
                {
                    Project project = GetProject(item.pHier);
                    String message = "";

                    switch (command_id)
                    {
                        case PkgCmdIDList.CommandIdExecuteQMake:
                            logger.WriteOutputPane("Updating project : " + project.Name);
                            message = "Project " + project.Name;
                            if (mQtSolution.UpdateProject(project.FullName))
                            {
                                message += " update successfully done !";
                            }
                            else
                            {
                                message += " update failed !";
                            }

                            logger.WriteOutputPane(message);
                            break;
                    }
                }
            }
        }



        private void OnSolutionOpened()
        {
            OutputPane logger = Services.Instance.Logger;
            logger.ShowOutputPane();

            logger.WriteOutputPane("Solution opened.");

            if (mQtSolution != null) mQtSolution = null;

            mQtSolution = new QtSolution();
            mQtSolution.BuildDependencies();

        }

        private void OnSolutionRenamed(string OldName)
        {
            OutputPane logger = Services.Instance.Logger;
            logger.ShowOutputPane();

            logger.WriteOutputPane("Solution renamed.");
        }


        public Project GetProject(IVsHierarchy hierarchy)
        {
            object project;

            ErrorHandler.ThrowOnFailure
                (hierarchy.GetProperty(
                    VSConstants.VSITEMID_ROOT,
                    (int)__VSHPROPID.VSHPROPID_ExtObject,
                    out project));

            return (project as Project);
        }

        private ICollection GetSelectedItems()
        {
            IVsMonitorSelection monitorSelection    = GetService(typeof(IVsMonitorSelection)) as IVsMonitorSelection;
            IntPtr hierarchy_ptr                    = IntPtr.Zero;
            uint item_id                            = 0;
            IVsMultiItemSelect multi_item_selection = null;
            IntPtr selection_container              = IntPtr.Zero;

            ErrorHandler.ThrowOnFailure(monitorSelection.GetCurrentSelection(out hierarchy_ptr, out item_id, out multi_item_selection, out selection_container));

            List<VSITEMSELECTION> selectedNodes = new List<VSITEMSELECTION>();

            try
            {
                if(item_id == VSConstants.VSITEMID_NIL) // No selection.
                {

                }
                else if (item_id != VSConstants.VSITEMID_SELECTION) // Single selection.
                {
                    if (hierarchy_ptr == IntPtr.Zero) // Solution selected.
                    {
                        VSITEMSELECTION vsItemSelection;
                        vsItemSelection.pHier  = null;
                        vsItemSelection.itemid = item_id;

                        selectedNodes.Add(vsItemSelection);
                    }
                    else // Project selected.
                    {
                        IVsHierarchy hierarchy = (IVsHierarchy)Marshal.GetObjectForIUnknown(hierarchy_ptr);
                        
                        VSITEMSELECTION vsItemSelection;
                        vsItemSelection.pHier  = hierarchy;
                        vsItemSelection.itemid = item_id;

                        selectedNodes.Add(vsItemSelection);
                    }
                }
                else // Multiple selections.
                {
                    if (multi_item_selection != null)
                    {
                        // Get number of items selected and also determine if the items are located in more than one hierarchy.
                        uint number_of_selected_items = 0;
                        int is_single_hierarchy       = 0;

                        ErrorHandler.ThrowOnFailure(multi_item_selection.GetSelectionInfo(out number_of_selected_items, out is_single_hierarchy));

                        // Now loop all selected items and add them to the list.
                        Debug.Assert(number_of_selected_items > 0, "Bad number of selected items");

                        if (number_of_selected_items > 0)
                        {
                            VSITEMSELECTION[] vsItemSelections = new VSITEMSELECTION[number_of_selected_items];
                            ErrorHandler.ThrowOnFailure(multi_item_selection.GetSelectedItems(0, number_of_selected_items, vsItemSelections));

                            foreach (VSITEMSELECTION vsItemSelection in vsItemSelections)
                            {
                                selectedNodes.Add(vsItemSelection);
                            }
                        }
                    }
                }
            }
            catch (Exception exception)
            {
                throw exception;
            }
            finally
            {
                if(hierarchy_ptr != IntPtr.Zero)       Marshal.Release(hierarchy_ptr);
                if(selection_container != IntPtr.Zero) Marshal.Release(selection_container);
            }

            return selectedNodes;
        }
    }
}
