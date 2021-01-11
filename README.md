# GanttGen

Generates html based gantt charts from given project with tasks

The input project file is xml based

Sample project files can be found in [`tests/`](tests/)

## Sample usage:
To create charts for the test projects use these commands
```
help

generate ../tests/project1.xml output1.html MIN_TIME
generate ../tests/project1.xml output2.html MIN_PEAK

generate ../tests/project2.xml output3.html MIN_TIME
```

## Documentation

To generate documentation run this command in [`docs/`](docs/)
```
doxygen Doxyfile
```
