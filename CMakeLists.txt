cmake_minimum_required(VERSION 3.26)
project(Project)

set(CMAKE_CXX_STANDARD 17)

add_executable(Project main.cpp
        ToolBar/ToolBar.h
        ToolBar/Draw.h
        ToolBar/MenuIDs.h
        Curves/Bezier.h
        Classes/Paint.h
        Classes/Point.h
        Classes/Point.h
        ToolBar/ColorPicker.h
        ToolBar/CursorChanger.h
        Files/Cursors/cursor.cur
        Clipping/Rectangle&Square/PointClipping.h
        Clipping/Rectangle&Square/LineClipping.h
        Shapes/Line/BresenhamLine.h
        Clipping/Rectangle&Square/PolygonClipping.h
        Utilities/fileUtilitis.h
        Utilities/fileUtilitis.h
        Shapes/Ellipse/MidpointEllipse.h
        Shapes/Ellipse/standardEllipse.h
        Filling/ConvexFill.h
        Filling/GeneralPolygonFill.h
        Filling/iterativeFloodFill.h
        Filling/recursiveFloodFill.h
        Curves/CardinalSplineCurve.h

)

set_target_properties(Project PROPERTIES
        LINK_FLAGS "-mwindows"
)
# Link to GDI32 for Windows graphics
#target_link_libraries(Project gdi32 user32)

