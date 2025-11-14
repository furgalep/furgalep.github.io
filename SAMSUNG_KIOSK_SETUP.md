# Samsung Galaxy A9 Kiosk Mode Setup Guide

## Method 1: Install as PWA (Progressive Web App) - Recommended

1. **Open the site** in Samsung Internet browser:
   - Navigate to: `https://furgalep.github.io/`

2. **Install the app**:
   - Tap the **menu** (three dots) in the browser
   - Select **"Add page to"** → **"Home screen"**
   - Or tap **"Install app"** if available in the menu

3. **Launch from home screen**:
   - The app will appear as an icon on your home screen
   - Tap it to launch in standalone mode (no browser UI)

4. **Enter fullscreen**:
   - The app will automatically attempt to enter fullscreen
   - If prompted, tap "Allow" to enter fullscreen mode

## Method 2: Samsung Kiosk Mode (Samsung Knox)

If you have Samsung Knox or Enterprise features:

1. **Enable Kiosk Mode**:
   - Go to **Settings** → **Advanced features** → **Kiosk mode**
   - Or use **Samsung Knox** if available

2. **Set the app as kiosk**:
   - Add the PWA (from Method 1) to kiosk mode
   - This will lock the device to only show this app

## Method 3: Samsung Internet Fullscreen Mode

1. **Open Samsung Internet**:
   - Navigate to the site

2. **Enter fullscreen**:
   - Tap the **menu** (three dots)
   - Select **"Full screen"** or **"Hide toolbar"**
   - The browser UI will hide

3. **Lock screen orientation**:
   - Swipe down from top to access quick settings
   - Enable **"Screen rotation lock"** (portrait mode)

## Troubleshooting

### Browser UI Still Showing
- Make sure you installed as PWA (Method 1)
- Try clearing browser cache and reinstalling
- Check if Samsung Internet is updated to latest version

### Can't Enter Fullscreen
- Some browsers require user interaction first
- Tap anywhere on the screen to trigger fullscreen
- Check browser permissions for fullscreen

### Screen Rotation Issues
- Lock rotation in Android settings
- The app is optimized for portrait mode

### App Not Installing
- Make sure you're accessing via HTTPS (GitHub Pages uses HTTPS)
- Check that `manifest.json` is accessible
- Try clearing browser cache

## Additional Tips

- **Disable notifications**: Go to Settings → Apps → Samsung Internet → Notifications → Off
- **Disable auto-update**: Prevent browser updates that might change behavior
- **Set as default**: Make Samsung Internet the default browser
- **Disable other apps**: Use Samsung's Focus Mode or App Blocking to prevent access to other apps

## For True Kiosk Mode (Device Lockdown)

If you need complete device lockdown:

1. **Use Samsung Knox** (if available on your device)
2. **Use a third-party kiosk app** like:
   - Fully Kiosk Browser
   - KioWare
   - SureLock
3. **Configure Android Enterprise** (for managed devices)

These methods will lock the device to only show your app with no way to exit.


