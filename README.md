Dev Setup
---------
1. Install python 3.8
2. Run `pip install pipenv` to install pipenv
3. Run `pipenv install` to bring in dependencies
4. Launch the game by running `pipenv run python main.py`

####Profiling
 * To enable profiling, launch the game with the `--profile` option. 
    e.g.
   `pipenv run python main.py --profile`
 * To view a profile result, run the following command:
   `pipenv run snakeviz <.prof file>`
