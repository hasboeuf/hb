using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Text.RegularExpressions;


using EnvDTE;
using EnvDTE80;

namespace hb
{
    class QtSolution : QtProFile
    {
        #region Attributes
        private Solution mSolution;
        private SolutionEvents mEvents;
        private Dictionary<String, QtProject> mProjects;
        private SubDirs mSubDirs;
        private List<Dependency> mDependencies;

        public Solution Instance
        {
            get
            {
                return mSolution;
            }
        }

        public DTE2 Automation
        {
            get;
            private set;
        }

        #endregion

        #region Constructors
        public QtSolution() :
            base(Services.Instance.Automation.Solution.FullName, null)
        {
            Automation = Services.Instance.Automation;
            mSolution = Automation.Solution;
            mSubDirs = null;
            mDependencies = null;

            mEvents = Automation.Events.SolutionEvents;
            mEvents.ProjectAdded   += new _dispSolutionEvents_ProjectAddedEventHandler(OnProjectAdded);
            mEvents.ProjectRemoved += new _dispSolutionEvents_ProjectRemovedEventHandler(OnProjectRemoved);
            
            mProjects = new Dictionary<String, QtProject>();

            foreach(Project p in mSolution.Projects)
            {
                OnProjectAdded(p);
            }
            
            ParseQMakeFile();
        }
        #endregion

        #region Events

        private void OnProjectAdded(Project project)
        {
            if (project != null)
            {
                if (!mProjects.ContainsKey(project.FullName))
                {
                    if (project.Kind.Equals("{8BC9CEB8-8B4A-11D0-8D11-00A0C91BC942}"))
                    {
                        mProjects[project.FullName] = new QtProject(this, project);
                    }
                }
            }
        }

        private void OnProjectRemoved(Project project)
        {
            if (project != null)
            {
                mProjects.Remove(project.FullName);
            }
        }
        #endregion

        #region Methods
        private void ParseQMakeFile()
        {
            mSubDirs = new SubDirs(this);
            mDependencies = new List<Dependency>();

            if (IsValid)
            {
                StreamReader reader = null;

                try
                {
                    reader = new StreamReader(QMakeFile);
                }
                catch (System.Exception)
                {
                    return;
                }

                String pattern_depends = @"^(\S+)(\.depends)(\s*)="; // Example: network.depends =
                String pattern_subdirs = @"^(SUBDIRS)(\s*)(\+=)"; // Example: SUBDIRS +=

                Regex regex_depends = new Regex(pattern_depends);
                Regex regex_subdirs = new Regex(pattern_subdirs);

                String line = null;

                while (!reader.EndOfStream)
                {
                    line = reader.ReadLine();
                    Console.WriteLine("\nLINE:{0}", line);

                    if (regex_depends.IsMatch(line))
                    {

                        if (line.EndsWith(@"\")) // Multi-line depends statement.
                        {
                            bool keep_reading = true;
                            while (!reader.EndOfStream && keep_reading)
                            {
                                line += reader.ReadLine();
                                if (!line.EndsWith(@"\")) keep_reading = false;
                            }
                        }

                        line = line.Trim(); // Remove extra whitespace at the end.
                        String project_name = line.Substring(0, line.IndexOf(".depends")); // Retrieve project name.

                        line = line.Substring(line.IndexOf("=") + 1);
                        line = line.Replace(@"\", String.Empty); // Remove potential backslashes.
                        String[] project_depends = line.Split(new char[0], StringSplitOptions.RemoveEmptyEntries); // new char[0] is considered as all whitespaces.

                        Console.WriteLine("\nMATCH:{0}|", line);

                        Dependency dependency = new Dependency(this);
                        dependency.Source = project_name;
                        foreach(String project_depend in project_depends)
                        {
                            dependency.AddTarget(project_depend);
                        }
                        
                        mDependencies.Add(dependency);
                    }
                    else if (regex_subdirs.IsMatch(line))
                    {
                        if (line.EndsWith(@"\")) // Multi-line subdirs statement.
                        {
                            bool keep_reading = true;
                            while (!reader.EndOfStream && keep_reading)
                            {
                                line += reader.ReadLine();
                                if (!line.EndsWith(@"\")) keep_reading = false;
                            }
                        }

                        line = line.Trim(); // Remove extra whitespace at the end.
                        line = line.Substring(line.IndexOf("=") + 1);
                        line = line.Replace(@"\", String.Empty); // Remove potential backslashes.
                        String[] project_subdirs = line.Split(new char[0], StringSplitOptions.RemoveEmptyEntries); // new char[0] is considered as all whitespaces.

                        foreach(String project_subdir in project_subdirs)
                        {
                            mSubDirs.AddPath(project_subdir);
                        }
                        
                    }
                }

                reader.Close();

                OutputPane logger = Services.Instance.Logger;
                logger.ShowOutputPane();
                logger.WriteOutputPane(mSubDirs.ToString());
                foreach(Dependency dependency in mDependencies)
                {
                    logger.WriteOutputPane(dependency.ToString());
                }
            }
        }

        public void UpdateSolution()
        {
            Environment environment = Services.Instance.Env;

            if (environment.IsValid && base.IsValid)
            {
                Shell shell = Services.Instance.Shell;
                List<String> commands = new List<String>();

                commands.Add("qmake -set QMAKESPEC " + environment.QMakeSpec);
                commands.Add("qmake -tp vc -recursive");

                mSolution.Close(true);
                mProjects.Clear();

                shell.Add(commands);
                shell.Execute(DirName);

                Automation.Solution.Open(FullName);
                mSolution = Automation.Solution;

                foreach (Project project in mSolution.Projects)
                {
                    OnProjectAdded(project);
                }

                ParseQMakeFile();
                //BuildDependencies();

                Automation.Solution.SaveAs(FullName);
            }
        }

        public bool UpdateProject(String fullname_project)
        {
            if (mProjects.ContainsKey(fullname_project))
            {
                mProjects[fullname_project].UpdateProject();
                return true;
            }
            else
            {
                return false;
            }
        }

        public void BuildDependencies()
        {
            foreach (Dependency dependency in mDependencies)
            {
                dependency.Resolve(GetProjects());

                if (dependency.IsValid())
                {
                    BuildDependencies depends = mSolution.SolutionBuild.BuildDependencies; // TODO Improve the search method.
                    for(int i = 1; i <= depends.Count; ++i)
                    {
                        BuildDependency depend = depends.Item(i);
                        if(dependency.Source.Contains(depend.Project.Name))
                        {
                            depend.RemoveAllProjects();
                            foreach (String target in dependency.Targets)
                            {
                                depend.AddProject(target);
                            }
                        }
                    }
                }
            }
        }

        public void BuildDependencies(QtProject project)
        {
            if (mProjects.ContainsValue(project))
            {
                foreach (Dependency dependency in mDependencies)
                {
                    dependency.Resolve(project);

                    if (dependency.IsValid())
                    {

                        BuildDependencies depends = mSolution.SolutionBuild.BuildDependencies; // TODO Improve the search method.
                        for (int i = 1; i <= depends.Count; ++i)
                        {
                            BuildDependency depend = depends.Item(i);
                            if (dependency.Source.Contains(depend.Project.Name))
                            {
                                depend.RemoveAllProjects();
                                foreach (String target in dependency.Targets)
                                {
                                    depend.AddProject(target);
                                }
                            }
                        }
                    }
                }
            }
        }

        public List<QtProject> GetProjects()
        {
            return new List<QtProject>(mProjects.Values);
        }

        #endregion

    }
}
