using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace hb
{
    internal class DebugSettings
    {
        #region Attributes

        public QtProject Parent
        {
            get;
            private set;
        }

        public List<String> Arguments
        {
            get;
            private set;
        }

        public List<String> LibPaths
        {
            get;
            private set;
        }

        #endregion

        #region Constructors

        public DebugSettings(QtProject project)
        {
            Parent    = project;
            Arguments = new List<String>();
            LibPaths  = new List<String>();
        }

        #endregion

        #region Methods

        public void AddArguments(String arguments)
        {
            if (arguments.Contains("$${PWD}"))
                arguments = arguments.Replace("$${PWD}", Parent.DirName);

            Arguments.Add(Parent.Resolve(arguments).Trim());
        }

        public void AddPath(String paths)
        {
            char[] separators = new char[] { ' ', '\t' };
            String[] items = paths.Split(separators, StringSplitOptions.RemoveEmptyEntries);

            foreach (String item in items)
            {
                String path = item.Trim().Replace("/", "\\");

                path = Parent.Resolve(path);
                path = path.Replace("$(", "%").Replace(")", "%");

                LibPaths.Add(path);
            }
        }
        #endregion
    }
}
