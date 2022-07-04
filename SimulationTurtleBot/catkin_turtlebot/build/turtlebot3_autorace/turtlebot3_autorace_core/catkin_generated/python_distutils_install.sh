#!/bin/sh

if [ -n "$DESTDIR" ] ; then
    case $DESTDIR in
        /*) # ok
            ;;
        *)
            /bin/echo "DESTDIR argument must be absolute... "
            /bin/echo "otherwise python's distutils will bork things."
            exit 1
    esac
fi

echo_and_run() { echo "+ $@" ; "$@" ; }

echo_and_run cd "/home/pedrolucas/catkin_turtlebot/src/turtlebot3_autorace/turtlebot3_autorace_core"

# ensure that Python install destination exists
echo_and_run mkdir -p "$DESTDIR/home/pedrolucas/catkin_turtlebot/install/lib/python3/dist-packages"

# Note that PYTHONPATH is pulled from the environment to support installing
# into one location when some dependencies were installed in another
# location, #123.
echo_and_run /usr/bin/env \
    PYTHONPATH="/home/pedrolucas/catkin_turtlebot/install/lib/python3/dist-packages:/home/pedrolucas/catkin_turtlebot/build/lib/python3/dist-packages:$PYTHONPATH" \
    CATKIN_BINARY_DIR="/home/pedrolucas/catkin_turtlebot/build" \
    "/usr/bin/python3" \
    "/home/pedrolucas/catkin_turtlebot/src/turtlebot3_autorace/turtlebot3_autorace_core/setup.py" \
     \
    build --build-base "/home/pedrolucas/catkin_turtlebot/build/turtlebot3_autorace/turtlebot3_autorace_core" \
    install \
    --root="${DESTDIR-/}" \
    --install-layout=deb --prefix="/home/pedrolucas/catkin_turtlebot/install" --install-scripts="/home/pedrolucas/catkin_turtlebot/install/bin"
