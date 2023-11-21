# Overview

Dynamate is a graphics engine for building small, 2D graphics applications that run in transparent windows!

Dynamate reads from the "dynamate/scenes" directory and draws the scenes as specified. It reads objects, textures, and shaders from scenes
stored in the "scenes" dynamate/directory, sends them into the OpenGL rendering pipeline, and they then get drawn to your screen.

# How To Create a Scene

    - Create a folder in the "dynamate/scenes" directory, and title it what you'd like to call the scene.
    - Create a file called "index.txt" within the new folder and open it for editing.
    - Add "#dynamo" onto the top line. Dynamate checks this line to make sure it's a Dynamate scene that it's loading.
    - Add "objects:x" on the second line, where x is the number of objects you'd like to have in your scene.
    - From here, everything line follows a "key:value" structure, where you specify the attribute first, followed by the value.
        - The order of the keys doesn't matter, Dynamate can read them as they come. For simplicity, I'll stick with the shown order
    - Key:Value
        - numberOfVertices:9
            - takes an integer
        - vertices:-0.5,-0.5,0.0,0.5,-0.5,0.0,0.0,0.5,0.0
            - a comma separated array of floats. no spaces between.
            - every three floats make a single vertex, and they follow a "x,y,z" pattern.
        - position:0.0,3.0,5.0
            - a comma separated array of flats, no spaces between.
            - these are xyz-coordinates.
            - the orthogonal perspective disregards the Z-value. X and Y are limited to between -5.0 and 5.0.
        - vertexShader:shaders/vertShader.glsl
            - this is the filepath to a GLSL shader. the parent directory is your scene folder within "dynamate/scenes"
        - fragmentShader:shaders/fragShader.glsl
            - this is the filepath to a GLSL shader. the parent directory is your scene folder within "dynamate/scenes"
    - After you've specified all the "key:value" pairs for the object, add "endObject" to the line below the last pair
        - this is a keyword that lets Dynamate know that the object is finished being specified.
    - Create GLSL shaders in the place that you specified in the "key:value" pairs, with the same name.
        - If you don't know how to create GLSL shaders, you can simply copy the shaders from the default scene.
