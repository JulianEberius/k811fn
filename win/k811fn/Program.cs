using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace k811fn
{
    public class K811fn : Form
    {

        [DllImport("lib\\libk811fn.dll")]
        public static extern bool setNormal();

        [DllImport("lib\\libk811fn.dll")]
        public static extern bool setSpecial();

         [STAThread]
        public static void Main()
        {
            Application.Run(new K811fn());
        }
 
        private NotifyIcon  trayIcon;
        private ContextMenu trayMenu;
 
        public K811fn()
        {
            // Create a simple tray menu with only one item.
            trayMenu = new ContextMenu();
            trayMenu.MenuItems.Add("Use as F-Keys", OnNormal);
            trayMenu.MenuItems.Add("Use as special function keys", OnSpecial);
            trayMenu.MenuItems.Add("Exit", OnExit);
 
            // Create a tray icon. In this example we use a
            // standard system icon for simplicity, but you
            // can of course use your own custom icon too.
            trayIcon      = new NotifyIcon();
            trayIcon.Text = "K811fn";
            trayIcon.Icon = Properties.Resources.mainIcon;
 
            // Add menu to tray icon and show it.
            trayIcon.ContextMenu = trayMenu;
            trayIcon.Visible     = true;
        }
 
        protected override void OnLoad(EventArgs e)
        {
            Visible       = false; // Hide form window.
            ShowInTaskbar = false; // Remove from taskbar. 
            base.OnLoad(e);
        }
 
        private void OnExit(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void configureDevice(Func<bool> confFunction) {
            var success = confFunction();
            if (success) {
                trayIcon.BalloonTipText = "Successfully changed settings";
            } else {
                trayIcon.BalloonTipText = "Failed to change settings";
            }
            trayIcon.BalloonTipTitle = "K811fn";
            trayIcon.ShowBalloonTip(5);
        }

        private void OnNormal(object sender, EventArgs e)
        {
            configureDevice(setNormal);
        }

        private void OnSpecial(object sender, EventArgs e)
        {
            configureDevice(setSpecial);
        }
 
        protected override void Dispose(bool isDisposing)
        {
            if (isDisposing)
            {
                // Release the icon resource.
                trayIcon.Dispose();
            }
 
            base.Dispose(isDisposing);
        }
    }
}
