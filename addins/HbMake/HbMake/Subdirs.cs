using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace hb
{
    internal class SubDirs
    {
        #region Attributes

        public QtSolution Parent
        {
            get;
            private set;
        }

        public List<String> Dirs
        {
            get;
            private set;
        }

        #endregion

        #region Constructors

        public SubDirs(QtSolution solution)
        {
            Parent = solution;
            Dirs = new List<String>();
        }

        #endregion

        #region Methods

        public void AddPath(String paths)
        {
            char[] separators = new char[] { ' ', '\t' };
            String[] items = paths.Split(separators, StringSplitOptions.RemoveEmptyEntries);

            foreach (String item in items)
            {
                String path = item;

                if (path.Contains(".pro"))
                    path = path.Remove(path.LastIndexOf("/"));

                path = path.Trim().Replace("/", "\\");
                Dirs.Add(Parent.DirName + path);
            }
        }

        public override string ToString()
        {
            String to_string = "";

            to_string += "SubDirs: ";
            foreach (String dir in Dirs)
            {
                to_string += dir + " ";
            }
            to_string += "\n";

            return to_string;
        }

        #endregion
    }
       
}
