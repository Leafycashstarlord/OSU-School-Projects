# Assignment 1
**Assignment and Code Blog entry due at 11:59pm on Monday, 10/12/2020**<br/>
**Demo due by 11:59pm on Monday 10/26/2020**

This assignment is intended to get you up and running with some of the tools we'll be using in this course and also to get you to start using HTML to create web pages.  It should be very straightforward.  It has three parts, described below.

## 1. Sign up for Piazza

Use this link to sign up for CS 290 on Piazza using your ONID email address: https://piazza.com/oregonstate/fall2020/cs290

We'll be using Piazza in this course for Q&A because it's geared towards students helping other students with the class.  Anyone can post or answer a question on Piazza, even anonymously, and the instructor and TAs can revise and endorse student answers, which means you can be confident in the quality of the response.

You are *strongly encouraged* to post any class-related questions to Piazza first instead of emailing the instructor or TAs.  You should also get in the habit of checking in to Piazza to answer other students' questions.  This will not only enable everyone to get help quickly, but it will also help you improve your understanding of the material, since teaching someone else is the best way to learn something.

As an incentive to use Piazza, extra credit will be awarded to the most active Piazza participants at the end of the class.

## 2. Use Git and GitHub and start practicing HTML

The other tool we'll be using quite a bit for this course is Git/GitHub.  You're already here looking at this assignment, so we know you've got at least some Git/GitHub skills.  Practice a little more and also start using HTML by following these steps:

1. If you're new to Git and GitHub, take a few minutes to play with Git-it, which is a desktop app that teaches you how to use Git and GitHub:

    https://github.com/jlord/git-it-electron#git-it-desktop-app

    We'll be using Git and GitHub heavily in this course, so it'll pay off to put in the time now to learn how to use them.

2. Clone this assignment repository from GitHub onto your development machine. Within the cloned assignment directory on your development machine, create a new file `index.html` that contains a complete HTML-only page (no CSS or JS required yet, but feel free to use them if you want) that displays these things:
    * Your name and what you prefer to be called (if it's different from your name).
    * Your OSU email address (e.g. `hessro@oregonstate.edu`).
    * Your major and year of study.
    * The answer to this question: what is the most complex or interesting thing you've done with your current web development skills?  If you've never done anything related to web development, that's fine, but make sure to say that here.
    * The answer to this question: what do you hope to learn from this class?
    * The answer to this question: have you signed up for our course Piazza forum?
    * A description of the most interesting fact about you or the most unique experience you've had.  Include only what you can think of and write down in two minutes, maximum.
    * A photo with a clear picture of your face (using an `<img>` tag).

    This info should be well-structured, e.g. using headings (`<h1>`, `<h2>`, `<h3>`, etc.), paragraphs (`<p>`), an unordered list (`<ul>` and `<li>`), a combination of those things, or anything else that makes sense.

3. Use Git commands to add and commit your new file to the local assignment repository on your development machine and to push the changes in your local repository back to your remote assignment repository on GitHub.

4. Add to your assignment directory a new file `blog.html` that contains an HTML-only page (again, feel free to add CSS and/or JS if you want, but that's not required) that will contain your code blog for the whole term.  In this file, you should start your code blog with a single entry reflecting on your experience completing this assignment.  Here are some example questions you might answer, but feel free to reflect in any way you wish, beyond these questions:
    * What challenges or troubles did you have completing this assignment.  How did you work through them?
    * What did you learn from this assignment?  What did you already know?
    * What resources (e.g. specific web articles, the class Piazza forum, the TAs) were most helpful in completing this assignment?  How did you use these resources?

    Again, your blog page should be nicely structured, with a title at the top and a title and date for your first post.  You should also include a link at the top of your blog page that goes back to `index.html`.

5. Use Git commands to add and commit your new file to the local assignment repository on your development machine and to push the changes in your local repository back to your remote assignment repository on GitHub.

6. Commit and push an update to your `index.html` file adding a link near the top of the page to your code blog in `blog.html`.

## 3. Publish your newly-created pages

The last thing you'll do for this assignment is publish your newly created pages on the web.  You have two options for how to do this:
  1. Publish your index and blog pages under your personal ENGR web space (or ONID, if you're not an Engineering student) under a URL like this: http://web.engr.oregonstate.edu/~YOUR_ONID_ID/cs290/.  For help publishing to your web space, see one of these pages (more tips are included below):
      * ENGR: http://it.engineering.oregonstate.edu/where-do-i-put-my-personal-webpages
      * ONID: https://oregonstate.teamdynamix.com/TDClient/KB/ArticleDet?ID=45669

  2. Publish your pages using GitHub Pages: https://pages.github.com/.

However you publish your pages, make sure to visit them on the internet (i.e. using a URL that starts with `https://` or `http://` and NOT one that starts with `file://`), and make sure they look the way you expect them to look.

## Tips on publishing to OSU web space

Here are a few helpful hints on getting your pages published to one of your OSU web spaces (either ENGR or ONID):

  * The main way to publish content on either the ENGR web space or the ONID web space is to put files in the `public_html/` directory that lives in your home directory on the ENGR/ONID servers.  You can do this in any number of ways:
      * [Using Windows file sharing](https://it.engineering.oregonstate.edu/accessing-engineering-file-space-using-windows-file-sharing).  Once you can access your `public_html/` directory this way, all you need to do is put your HTML files inside.
      * Using one of the methods [described here](https://it.engineering.oregonstate.edu/accessing-engineering-file-space).
      * Using SSH/SFTP, e.g. using [MobaXterm](https://mobaxterm.mobatek.net/documentation.html#2_3_3) or [FileZilla](https://filezilla-project.org/).

  * Make sure to publish *all* of the files needed by your pages, including HTML files, image files, etc.

  * Once you have the files you want to publish put inside `public_html/`, the web URLs of those files match the directory structure underneath `public_html/`.  For example, say the contents of your `public_html/` directory on the ENGR servers look like this:

      ```
      public_html/
        index.html
        blog.html
      ```

    Then the two files inside `public_html/` will be available at the following two URLs (if you publish on your ONID web space, then the URLs will begin with `people.oregonstate.edu` instead of `web.engr.oregonstate.edu`):

      * http://web.engr.oregonstate.edu/~YOUR_ONID_ID/index.html
      * http://web.engr.oregonstate.edu/~YOUR_ONID_ID/blog.html

    If, instead, your files live in a subdirectory within `public_html/` on the ENGR servers (e.g. `public_html/cs290/`) like this:

      ```
      public_html/
        cs290/
          index.html
          blog.html
      ```

    then those files will be available at the following two URLs:

      * http://web.engr.oregonstate.edu/~YOUR_ONID_ID/cs290/index.html
      * http://web.engr.oregonstate.edu/~YOUR_ONID_ID/cs290/blog.html

  * To be viewable on the web, the files inside your `public_html/` directory need to have the correct Unix permissions.  Specifically, all files need to have *read* permission granted for the world, and all subdirectories within `public_html/` need to have *read* and *execute* permission granted for the world.  You can read more about Unix permissions here:

      https://www.tutorialspoint.com/unix/unix-file-permission.htm

    Once you understand how Unix permissions work, make sure all of your files have permissions that look something like this: `-rw-r--r--` (i.e. `644` permissions), and make sure the subdirectories under `public_html/` have permissions that look something like this: `-rwxr-xr-x` (i.e. `755` permissions).

  * You should *never* use a URL that begins with `file:///...` within any of your HTML files.  Such a URL describes the location of a file *on a specific computer*.  If you need to refer to a local file, use a [relative URL](https://www.w3schools.com/html/html_filepaths.asp).


## Submission

We'll be using GitHub Classroom for this assignment, and you will submit your assignment via GitHub.  Just make sure your completed files are committed and pushed by the assignment's deadline to the master branch of the GitHub repo that was created for you by GitHub Classroom.  A good way to check whether your files are safely submitted is to look at the master branch your assignment repo on the github.com website (i.e. https://github.com/osu-cs290-f20/assignment-1-YourGitHubUsername/). If your changes show up there, you can consider your files submitted.

In addition to submitting your assignment via GitHub, you must submit the URL to your code blog entry (e.g. http://web.engr.oregonstate.edu/~YOUR_ONID_ID/cs290/blog.html) via Canvas by the due date specified above.

## Grading criteria

The assignment is worth 100 total points, broken down as follows:
* 40 points: Signed up for Piazza
* 40 points: Created `index.html` and `blog.html` with the requested structure and content and pushed them to GitHub
* 20 points: Published `index.html` and `blog.html` to your ENGR or ONID web space or to GitHub pages

In addition to your programming assignment grade, you will receive a pass/fail grade for your code blog entry, included in the code blog portion of your grade.
