# Vinylbro manual
## Cоздание личного репозитория с нужным .gitignore и простым README.MD

1. Login in gitlab and press "new project"
![](https://wiki.miem.hse.ru/5_%D1%80%D0%B5%D0%B4_0.png)
2. Create blank project
3. Write a name of repository and add gitignore settings if it's neccessary 
## Cоздание веток develop и master

1. Master branch auto created
2. Write in terminal git checkout -b develop  - it's to create a new branch
3. git push origin develop - it's to add new branch on gitlab

## Yстановка ветки develop по умолчанию

1. Navigate to the main page of the repository
2. Click  Settings
![](https://docs.github.com/assets/cb-28266/mw-1440/images/help/repository/repo-actions-settings.webp)
3. Under "Default branch", to the right of the default branch name and update
## Cоздание issue на создание текущего мануала
1. Navigate to the main page of the repository.
2. Click  Issues
![](https://docs.github.com/assets/cb-58284/mw-1440/images/help/repository/repo-tabs-issues-global-nav-update.webp)
3. Click New issue
![](https://docs.github.com/assets/cb-35272/mw-1440/images/help/issues/blank-issue-link.webp)
4. In the "Title" field, type a title for your issue. In the comment body field, type a description of your issue. 
5. Submit new issue
## Cоздание ветки по issue
1. Click  Issues.
2. In the list of issues, click the issue that you would like to create a branch for.
3. In the right sidebar under "Development", click Create a branch. If the issue already has a linked branch or pull request, select  and click Create a branch
![](https://docs.github.com/assets/cb-28716/mw-1440/images/help/issues/create-a-branch.webp)
4. Under "What's next", select whether you want to work on the branch locally or to open the branch in GitHub Desktop
## Cоздание merge request по ветке в develop
1. Click "Merge requests"
2. New merge request
3. Write changeas and click Compare branches and continue
![](https://338837155-files.gitbook.io/~/files/v0/b/gitbook-legacy-files/o/assets%2F-Lc9m5pdTeXvEkKkPMQr%2F-MRPWH8e7z7RyemHFA-M%2F-MRPX7tfzNvOQvPQBNgI%2Fimage.png?alt=media&token=566fe50f-b483-4e87-b034-c2189053739a)
## Kомментирование и принятие 
1. When it appeared, a dialogue opened, the presenter gave a description, added a comment, set the Milestone and chose which developer the MR would be sent to.
You can also specify that some kind of approval is required to accept a Merge request and merge into the master branch.
![](https://server-gu.ru/wp-content/uploads/2019/02/git-merge-request3.png)
2. Submit merge request
## формирование стабильной версии в master с простановкой тега
1. go to your repository
2. Repository > Tags
3. Add new tag
4. add title and description
5. Create tag
## работа с wiki проекта
After adding a project, the Wiki section is available in the menu on the left. You can add an unlimited number of pages with text materials. The Wiki is project specific.
The Home.mi home page is always added first. Wiki depends on the project.
The standard formatting method is Markdown. Preview mode is available in which you can see how the text will look.
