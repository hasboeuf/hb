using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;
using System.Diagnostics;


namespace hb
{
    internal class Shell
    {
        #region Attributes

        public List<String> Commands
        {
            get;
            private set;
        }

        #endregion

        #region Constructors

        public Shell()
        {
            Commands = new List<String>();
        }

        #endregion

        #region Methods

        public void Add(String command)
        {
            Commands.Add(command);
        }
        public void Add(List<String> commands)
        {
            foreach (String command in commands)
                Commands.Add(command);
        }
        public void Reset()
        {
            Commands.Clear();
        }

        /*public void Nmake(QtProject project, String config, String target)
        {
            Environment environment = Services.Subscribe().Environment();

            if (environment.IsValid() && project.IsValid())
                if (project.Architecture() != null)
                {
                    Shell shell = Services.Subscribe().Shell();

                    String makefile = "Makefile-";
                    makefile += environment.QtMakespec();
                    makefile += "_Qt" + environment.QtVersion();
                    makefile += "_" + project.Architecture();
                    makefile += "." + config;

                    List<String> commands = new List<String>();

                    commands.Add("\"" + environment.VCToolset() + "\" " + project.Architecture());
                    commands.Add("nmake /C /F \"" + makefile + "\" " + target);

                    shell.Add(commands);
                    shell.Execute(project.DirName());
                }
        }*/

        public void Execute(String working_dir)
        {
            if (Commands.Count > 0)
            {
                ProcessStartInfo startInfo = new ProcessStartInfo();
                System.Diagnostics.Process process = new System.Diagnostics.Process();

                startInfo.FileName = "cmd.exe";
                //startInfo.Arguments = "/Q /K PROMPT $S";
                startInfo.WorkingDirectory = working_dir;

                //startInfo.CreateNoWindow = true;
                //startInfo.WindowStyle = System.Diagnostics.ProcessWindowStyle.Hidden;

                startInfo.UseShellExecute = false;
                startInfo.RedirectStandardInput = true;
                startInfo.RedirectStandardOutput = true;
                startInfo.RedirectStandardError = true;

                process.StartInfo = startInfo;

                process.ErrorDataReceived  += WriteDataReceived;
                process.OutputDataReceived += WriteDataReceived;
                process.EnableRaisingEvents = true;

                process.Start();

                process.BeginOutputReadLine();
                process.BeginErrorReadLine();

                foreach (String command in Commands)
                {
                    process.StandardInput.WriteLine(command.Trim());
                }
                process.StandardInput.WriteLine("exit"); // Terminate cmd.exe.                    

                process.WaitForExit();
            }

            Commands.Clear();
        }

        void WriteDataReceived(object sender, DataReceivedEventArgs e)
        {
            Services.Instance.Logger.ShowOutputPane();
            Services.Instance.Logger.WriteOutputPane(e.Data);
        } 

        #endregion
    }
}
