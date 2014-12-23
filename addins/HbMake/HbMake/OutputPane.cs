using System;

using EnvDTE;
using EnvDTE80;

namespace hb
{
    internal class OutputPane
    {
        #region Attributes

        private DTE2 mAutomation;

        private bool mActivated;
        private OutputWindowPane mOutputPane;

        #endregion

        #region Constructors

        public OutputPane(DTE2 automation)
        {
            mAutomation = automation;

            Window window = mAutomation.Windows.Item(Constants.vsWindowKindOutput);
            OutputWindow outputWindow = (OutputWindow)window.Object;

            mActivated = false;
            mOutputPane = outputWindow.OutputWindowPanes.Add("HbMake");
        }

        #endregion

        #region Public Methods

        public void OpenOutputPane()
        {
            mOutputPane.Clear();
            mOutputPane.Activate();

            mActivated = true;
        }
        public void ShowOutputPane()
        {
            mOutputPane.Activate();
        }
        public void EnableOutputPane(bool status)
        {
            mActivated = status;
        }

        public void WriteOutputPane()
        {
            WriteOutputPane(null);
        }

        public void WriteOutputPane(String stream)
        {
            if (mActivated)
            {
                if (stream == null) mOutputPane.OutputString("\n");
                else mOutputPane.OutputString(stream + "\n");
            }
        }
        public void CloseOutputPane()
        {
            mOutputPane.Clear();
            mActivated = false;
        }

        #endregion

    }
}
