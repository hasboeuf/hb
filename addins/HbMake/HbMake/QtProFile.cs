using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

using EnvDTE;

namespace hb
{
    class QtProFile
    {

        #region Attributes
        public String FullName
        {
            get;
            private set;
        }
        public String FileName
        {
            get;
            private set;
        }

        public String DirName
        {
            get;
            private set;
        }
        
        public String Architecture
        {
            get;
            private set;
        }

        public String QMakeFile
        {
            get;
            private set;
        }

        public bool IsValid
        {
            get
            {
                return (QMakeFile != null);
            }
        }

        #endregion

        #region Constructors
        public QtProFile(String fullName, Configuration config)
        {
            FileInfo file_info = new FileInfo(FullName = fullName);
            FileName           = file_info.Name;
            DirName            = file_info.DirectoryName + "\\";
            Architecture       = null;
            QMakeFile          = null;

            DirectoryInfo directory = new DirectoryInfo(DirName);
            FileInfo[] qmake_files = directory.GetFiles("*.pro");

            if (config != null)
            {
                if (config.PlatformName.Equals("Win32")) Architecture = "x86";
                if (config.PlatformName.Equals("x64"))   Architecture = "x64";
            }

            if (qmake_files != null)
            {
                String error = null;
                String qmakespec = Services.Instance.Env.QMakeSpec;

                if (qmakespec == null)
                {
                    error += "Unable to resolve QMAKESPEC variable environment...";
                    qmake_files = null;
                }
                else if (qmake_files.Length < 1)
                {
                    error += "QMake file .pro not found. Unable to resolve QMake file associated to " + FileName + "...";
                    qmake_files = null;
                }
                else if (qmake_files.Length > 1)
                {
                    error += "Multiples QMake file .pro defined. Unable to resolve QMake file associated to " + FileName + "...";
                    qmake_files = null;
                }
                else
                {
                    QMakeFile = qmake_files[0].FullName;
                }

                if (error != null)
                {
                    OutputPane logger = Services.Instance.Logger;
                    logger.ShowOutputPane();
                    logger.WriteOutputPane(error);
                }
            }
        }
        #endregion

        #region Methods

        public String Resolve(String variable)
        {
            Environment environment = Services.Instance.Env;

            variable = variable.Replace("%OS%", "win32");
            variable = variable.Replace("%ARCH%", Architecture);
            variable = variable.Replace("%MAKESPEC%", environment.QMakeSpec);
            variable = variable.Replace("%QTVERSION%", environment.QtVersion);

            return variable;
        }

        #endregion
    }
}
