using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

using EnvDTE;
using EnvDTE80;

namespace hb
{
    class QtProject : QtProFile
    {
        #region Attributes

        public QtSolution Parent
        {
            get;
            private set;
        }

        public DebugSettings DebugSettings
        {
            get;
            private set;
        }

        public Project Instance
        {
            get
            {
                foreach (Project project in Parent.Instance.Projects)
                {
                    if (project.FullName == FullName) return project;
                }

                return null;
            }
        }

        #endregion

        #region Constructors

        public QtProject(QtSolution solution, Project project) :
            base(project.FullName, project.ConfigurationManager.ActiveConfiguration)
        {
            Parent = solution;
            DebugSettings = new DebugSettings(this);

            ParseQMakeFile();
            BuildDebugEnvironment();
        }

        #endregion

        #region Methods

        public void UpdateProject()
        {
            Environment environment = Services.Instance.Env;

            if (environment.IsValid && base.IsValid)
            {
                Shell shell = Services.Instance.Shell;
                List<String> commands = new List<String>();

                commands.Add("qmake -set QMAKESPEC " + environment.QMakeSpec);
                commands.Add("qmake -tp vc");

                shell.Add(commands);
                shell.Execute(DirName);

                ParseQMakeFile();
                //BuildDebugEnvironment();

                Parent.BuildDependencies(this);
            }
        }

        /*public void InstallProject()
        {
            Environment environment = Services.Instance.Environment();

            if (environment.IsValid && base.IsValid)
            {
                UpdateMakefile();

                Configuration configuration = Instance.ConfigurationManager.ActiveConfiguration;
                Configurations platform = Instance.ConfigurationManager.Platform(configuration.PlatformName);

                List<String> availables = new List<String>();
                foreach (Configuration available in platform)
                    availables.Add(available.ConfigurationName);

                Shell shell = Services.Instance.Shell;
                foreach (String available in availables)
                {
                    //shell.Nmake(this, available, "install");
                }
            }
        }*/

        /*public void UninstallProject()
        {
            Environment environment = Services.Instance.Env;

            if (environment.IsValid && base.IsValid)
            {
                UpdateMakefile();

                Configuration configuration = Instance.ConfigurationManager.ActiveConfiguration;
                Configurations platform = Instance.ConfigurationManager.Platform(configuration.PlatformName);

                List<String> availables = new List<String>();
                foreach (Configuration available in platform)
                    availables.Add(available.ConfigurationName);

                Shell shell = Services.Instance.Shell;
                foreach (String available in availables)
                {
                    //shell.Nmake(this, available, "uninstall");
                }
            }
        }*/

        public void UpdateMakefile()
        {
            Environment environment = Services.Instance.Env;

            if (environment.IsValid && base.IsValid)
            {
                if (Architecture != null)
                {
                    Shell shell = Services.Instance.Shell;
                    String qmakecmd = "qmake -o Makefile-";

                    qmakecmd += environment.QMakeSpec;
                    qmakecmd += "_Qt" + environment.QtVersion;
                    qmakecmd += "_" + Architecture;

                    shell.Add(qmakecmd);
                    shell.Execute(DirName);
                }
            }
        }

        public string GetDebugPath()
        {
            string debugPath = "";

            if (DebugSettings.LibPaths.Count > 0)
            {
                foreach (String path in DebugSettings.LibPaths)
                {
                    debugPath += (path + ";");
                }
            }

            return debugPath;
        }


        public void BuildDebugEnvironment()
        {
            if (DebugSettings.Arguments.Count > 0)
            {
                Project vcproject = Instance;
                ConfigurationManager configs = vcproject.ConfigurationManager;

                for (int i = 1; i <= configs.Count; i++)
                {
                    Configuration config = configs.Item(i);

                    bool needUpdate = false;

                    Property property = null;
                    try
                    {
                        property = config.Properties.Item("ConfigurationType");
                        if (property.Value.ToString() == "1")
                        {
                            needUpdate = true;
                        }
                    }
                    catch { }
                    if (needUpdate)
                    {
                        try
                        {
                            property = config.Properties.Item("CommandArguments");
                            string argumentsList = "";
                            foreach (String arguments in DebugSettings.Arguments)
                            {
                                argumentsList += (arguments + " ");
                            }
                            property.Value = argumentsList;
                        }
                        catch { }
                    }
                }
            }
        }

        #endregion

        #region Private Methods

        private void ParseQMakeFile()
        {
            DebugSettings = new DebugSettings(this);

            if (IsValid)
            {
                StreamReader reader = null;

                try { reader = new StreamReader(QMakeFile); }
                catch (System.Exception) { return; }

                bool arguments = false;
                bool libpaths = false;

                while (!reader.EndOfStream)
                {
                    String line = reader.ReadLine();
                    line = line.Trim();

                    if (line.Length > 0)
                    {
                        if (!arguments)
                            if (!line.StartsWith("#"))
                            {
                                arguments = (line.StartsWith("DEBUG.ARGS"));
                                if (arguments)
                                {
                                    if (libpaths) libpaths = false;
                                    line = line.Substring(line.IndexOf('=') + 1);
                                }
                            }

                        if (!libpaths)
                            if (!line.StartsWith("#"))
                            {
                                libpaths = (line.StartsWith("DEBUG.LIBPATH"));
                                if (libpaths)
                                {
                                    if (arguments) arguments = false;
                                    line = line.Substring(line.IndexOf('=') + 1);
                                }
                            }

                        if (arguments)
                        {
                            arguments = line.EndsWith("\\");

                            if (!line.StartsWith("#"))
                            {
                                if (arguments) line = line.Remove(line.LastIndexOf("\\"));
                                DebugSettings.AddArguments(line);
                            }
                        }

                        if (libpaths)
                        {
                            libpaths = line.EndsWith("\\");

                            if (!line.StartsWith("#"))
                            {
                                if (libpaths) line = line.Remove(line.LastIndexOf("\\"));
                                DebugSettings.AddPath(line);
                            }
                        }
                    }
                }

                reader.Close();
            }
        }

        #endregion
    }
}
