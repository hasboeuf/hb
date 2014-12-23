using System;
using System.ComponentModel.Design;
using System.Runtime.InteropServices;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using EnvDTE;
using EnvDTE80;

namespace hb
{
    // Singleton: http://jlambert.developpez.com/tutoriels/dotnet/implementation-pattern-singleton-csharp/
    internal sealed class Services
    {
        #region Attributes
        private static readonly Services msInstance = new Services();

        public DTE2 Automation
        {
            get;
            private set;
        }

        public OutputPane Logger
        {
            get;
            private set;
        }

        public Environment Env
        {
            get;
            private set;
        }

        private Shell mShell;
        public Shell Shell
        {
            get
            {
                if (mShell != null)
                {
                    mShell.Reset();
                }
                return mShell;
            }
            private set
            {
                mShell = value;   
            }
        }

        public static Services Instance
        {
            get
            {
                return msInstance;
            }
        }

        #endregion

        #region Constructors
        // Explicit static constructor to tell C# compiler
        // not to mark type as beforefieldinit
        static Services()
        {
        }

        private Services()
        {
            Automation = null;
            Logger     = null;
            Env        = null;
            mShell     = null;
        }

        #endregion

        #region Methods

        public void Init(DTE2 dte)
        {
            Automation = dte;
            Logger = new OutputPane(Automation);
            Env = new Environment(dte);
            Shell = new Shell();
        }

        #endregion

    }


}
