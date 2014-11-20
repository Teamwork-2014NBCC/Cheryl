Close all solutions before committing changes AND/OR syncing
Failure to do so will result in fucked up shit

Run the batch file in this directory. It will allow us to point to the Root of C: for our library/headers.


#####
More on the batch file
It creates a junction "C:\Libraries" which points to the github synchronized Libraries folder
This means we will all have the same libraries accessible from the same location on our HDDs