# GitHub Pages Setup Guide

Follow these steps to host your web app on GitHub Pages:

## Step 1: Create a GitHub Repository

1. Go to https://github.com/new
2. Create a new repository (e.g., `gigasprudel-timer` or `escape-room-timer`)
3. **Important**: Make it **public** (required for free GitHub Pages)
4. Do NOT initialize with README, .gitignore, or license (we'll add files manually)

## Step 2: Initialize Git and Push Files

Run these commands in your terminal (from the Arduino directory):

```bash
# Initialize git repository
git init

# Add all necessary files
git add index.html
git add 0_0.jpg 0_1.jpg 0_2.jpg 0_3.jpg
git add .gitignore
git add README.md

# Commit files
git commit -m "Initial commit: Gigasprudel 3000 Meistersender web app"

# Add your GitHub repository as remote (replace YOUR_USERNAME and REPO_NAME)
git remote add origin https://github.com/YOUR_USERNAME/REPO_NAME.git

# Push to GitHub
git branch -M main
git push -u origin main
```

## Step 3: Enable GitHub Pages

1. Go to your repository on GitHub
2. Click **Settings** tab
3. Scroll down to **Pages** section (in the left sidebar)
4. Under **Source**, select **Deploy from a branch**
5. Select branch: **main**
6. Select folder: **/ (root)**
7. Click **Save**

## Step 4: Access Your Site

Your site will be available at:
```
https://YOUR_USERNAME.github.io/REPO_NAME/
```

**Note**: It may take a few minutes for GitHub Pages to build and deploy your site.

## Troubleshooting

- If images don't load, make sure all image files (0_0.jpg through 0_3.jpg) are in the root directory
- If YouTube videos don't work, make sure you're accessing via HTTPS (GitHub Pages uses HTTPS by default)
- Check the repository Settings → Pages to see if there are any build errors


