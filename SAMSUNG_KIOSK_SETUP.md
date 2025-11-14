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

## Method 2: Android App Pinning (Built-in Alternative)

Most Android devices have App Pinning, which locks the device to a single app:

1. **Install the PWA** (from Method 1) first

2. **Enable App Pinning**:
   - Go to **Settings** → **Security** → **App pinning** (or **Settings** → **Advanced features** → **App pinning**)
   - Enable **"Lock device to pinned app"**

3. **Pin the app**:
   - Open the app from your home screen
   - Tap the **Recent Apps** button (square icon)
   - Swipe up on the app card and tap the **pin icon** (📌)
   - The device is now locked to this app

4. **To unpin**: Hold **Back** + **Recent Apps** buttons together

**Note**: Samsung Knox Kiosk Mode is only available on enterprise/knox-enabled devices. App Pinning works on most Android devices.

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

If you need complete device lockdown without any way to exit:

### Option 1: Third-Party Kiosk Apps (Recommended for non-Knox devices)

Install a dedicated kiosk browser app:

1. **Fully Kiosk Browser** (Free/Paid):
   - Install from Google Play Store
   - Set your URL: `https://furgalep.github.io/`
   - Configure to hide navigation, disable exit, lock orientation
   - Set as launcher app (replaces home screen)

2. **KioWare** (Paid, enterprise-focused)

3. **SureLock** (Paid, enterprise-focused)

### Option 2: Samsung Knox (Enterprise Devices Only)

- Only available on Samsung devices with Knox enabled
- Usually found on enterprise/business models
- If not available, use Option 1 or Method 2 (App Pinning)

### Option 3: Android Enterprise (For Managed Devices)

- Requires device enrollment in an MDM (Mobile Device Management) system
- Typically used in business/enterprise environments

**For most users**: Method 1 (PWA) + Method 2 (App Pinning) provides good kiosk-like behavior without additional software.


