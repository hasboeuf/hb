using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using EnvDTE;

namespace hb
{
    internal class Dependency
    {

        #region Attributes
        private QtSolution mParent;

        private String mSource;
        public String Source
        {
            get
            {
                return mSource;
            }
            set
            {
                if (value != null && !value.Equals(String.Empty))
                {
                    mSource = mParent.DirName + value.Trim().Replace("/", "\\");
                }
            }
        }

        public List<String> Targets
        {
            get;
            private set;
        }
        #endregion

        #region Constructors

        public Dependency(QtSolution solution)
        {
            mParent = solution;
            Source  = null;
            Targets = new List<String>();
        }

        #endregion

        #region Methods

        public void AddTarget(String target)
        {
            if(!target.Equals(String.Empty) && !Targets.Contains(target))
            {
                Targets.Add(target);
            }
        }

        public bool IsValid()
        {
            return (Source != null);
        }

        public void Resolve(QtProject project)
        {
            List<QtProject> projects = new List<QtProject>();
            projects.Add(project);

            Resolve(projects);
        }
        public void Resolve(List<QtProject> projects)
        {
            String srcResolved = "";
            List<String> tgtResolved = new List<String>();

            foreach (QtProject project in projects)
            {
                Project instance = project.Instance;

                if (project.FullName.Contains(Source))
                    srcResolved = instance.UniqueName;

                for (int i = 0; i < Targets.Count; ++i)
                {
                    if (project.FullName.Contains(Targets[i]))
                    {
                        tgtResolved.Add(instance.UniqueName);
                    }
                }
            }

            Source  = srcResolved;
            Targets = tgtResolved;
        }

        public override string ToString()
        {
            String to_string = "";

            to_string += "Source: " + Source + "\n";
            to_string += "Target: ";
            foreach(String target in Targets)
            {
                to_string += target + " ";
            }
            to_string += "\n";

            return to_string;
        }

        #endregion
    }
}
