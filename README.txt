Installing GTest:
=================

sudo aptitude install libgtest-dev
cd /usr/src/googletest/
sudo cmake .
sudo cmake --build . --target install


Building beegenerator:
======================

Create directory beegenerator/build (if not exists).
In beegenerator/build/
rm -r *
cmake ..
make


Testing:
========

in beegenerator/bin/
./Test


Running:
========
./beegenerator parameters.txt


Example for parameters.txt:
===========================


data_directory   /tmp/bees/               % e.g. /tmp/
number_of_digits     4                       % e.g. 3, then first image is /tmp/train_000.png
number_of_train_images          1000
number_of_val_images             400  
number_of_test_images            200  
number_of_steps_before_video_starts 1000     % steps carried out without making images. For avoiding
                                             % start effects at the beginning.

count_filename       /tmp/counts.txt         % Filename for saving the counts.
                                             % Format: "251 1 0" means: in image 251 one bee crossed
                                             %          from right to left and no bee from left to right.




image_width    50       %
image_height   100      %           border_width    image_width  border_width
border_width   300      %          ---------------------------------------------
x_count_line   100      %          |              |      .      |              |
                        %          |              |      .      |              |
                        %          |              |      .      |              |
                        %          |              |      .      |              |
                        %          |              |      .      |              |
                        %          |              |      .      |              |
                        %          |              |      .      |              |
                        %          |              |      .      |              |
                        %          |              |      .      |              |
                        %          |              |      .      |              |
                        %          ---------------------------------------------
                        %                                ^
                        %                           x_count_line
                        %
                        %   (bees are everywhere, but only the middle rectangle
                        %    is visible.)
                        %

color_of_bees     255 200 50  % RGB (0..255)
background_color   30 150 80  % RGB (0..255)

number_of_bees    200
radius_of_bees    5
min_start_speed   0
max_start_speed   0

brownian_probability 0.05  % Probability that a bee get a brownian hit during a step
brownian_strength   10     % Maximal strength of the brownian hit (random between 0 and this).

friction 0.001             % In each step, the velocity is reduced by:
                           %    (new velocity) = (1 - friction) * (old velocity)
