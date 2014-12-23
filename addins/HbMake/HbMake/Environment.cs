using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using EnvDTE;
using EnvDTE80;

namespace hb
{
    internal class Environment
    {
        #region Attributes
        public String QMakeSpec
        {
            get;
            set;
        }

        public String VCToolSet
        {
            get;
            private set;
        }

        public String QtVersion
        {
            get;
            private set;
        }

        public String EnvPath
        {
            get;
            private set;
        }

        public bool IsValid
        {
            get
            {
                return ((VCToolSet != null) &&
                        (QtVersion != null) &&
                        (QMakeSpec != null));
            }
        }

        #endregion

        #region Constructors
        public Environment(DTE2 automation)
        {
            QtVersion = "5";

            try
            {
                VCToolSet = null;

                if (automation.Version.Equals("9.0"))
                {
                    VCToolSet = System.Environment.GetEnvironmentVariable("VS90COMNTOOLS");
                }
                else if (automation.Version.Equals("10.0"))
                {
                    VCToolSet = System.Environment.GetEnvironmentVariable("VS100COMNTOOLS");
                }
                else if (automation.Version.Equals("12.0"))
                {
                    VCToolSet = System.Environment.GetEnvironmentVariable("VS120COMNTOOLS");
                }                    

                int index = VCToolSet.LastIndexOf(automation.Version) + automation.Version.Length;
                VCToolSet = VCToolSet.Remove(index) + "\\VC\\vcvarsall.bat";

                QMakeSpec = null;

                if (automation.Version.Equals("9.0"))
                {
                    QMakeSpec = "win32-msvc2008";
                }
                else if (automation.Version.Equals("10.0"))
                {
                    QMakeSpec = "win32-msvc2010";
                }
                else if (automation.Version.Equals("12.0"))
                {
                    QMakeSpec = "win32-msvc2013";
                }

                if (QMakeSpec != null)
                {
                    String qmakespec = System.Environment.GetEnvironmentVariable("QMAKESPEC");
                    if (QMakeSpec != qmakespec)
                    {
                        QMakeSpec = null;
                    }
                }

                if ((EnvPath = System.Environment.GetEnvironmentVariable("PATH")) != null)
                {
                    if (!EnvPath.Contains("DebugEnvVS"))
                    {
                        EnvPath = "%DebugEnvVS%;" + EnvPath;
                        System.Environment.SetEnvironmentVariable("PATH", EnvPath, EnvironmentVariableTarget.Process);
                    }
                }
            }
            catch (System.Exception e)
            {
                String exception = e.ToString();
                VCToolSet = null;
                QMakeSpec = null;
                QtVersion = null;
                EnvPath   = null;
            }


            String error = null;

            if (VCToolSet == null) error += "Visual C++ Toolset cannot be resolved";
            if (QMakeSpec == null) error += "Qt makespecs cannot be resolved";
            if (QtVersion == null) error += "Qt version cannot be resolved";
            if (EnvPath   == null) error += "PATH environment variable cannot be resolved";

            if (error != null)
            {
                Services.Instance.Logger.ShowOutputPane();
                Services.Instance.Logger.WriteOutputPane(error);
            }
        }
        #endregion
    }
}
