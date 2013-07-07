/* This file is part of the Pangolin Project.
 * http://github.com/stevenlovegrove/Pangolin
 *
 * Copyright (c) 2013 Steven Lovegrove
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef PANGOLIN_GLUT_BITMAP_H
#define PANGOLIN_GLUT_BITMAP_H
#ifndef HAVE_GLUT

#include <pangolin/glfont.h>

#ifdef HAVE_GLES
GLfloat g_raster_pos[4];

inline void glRasterPos3f(GLfloat x, GLfloat y, GLfloat z)
{
    // find object point (x,y,z)' in pixel coords
    GLdouble projection[16];
    GLdouble modelview[16];
    GLint    view[4];
    
    glGetDoublev(GL_PROJECTION_MATRIX, projection );
    glGetDoublev(GL_MODELVIEW_MATRIX, modelview );
    glGetIntegerv(GL_VIEWPORT, view );
    
    gluProject(x, y, z, modelview, projection, view,
        g_raster_pos, g_raster_pos + 1, g_raster_pos + 2);
}

inline void glRasterPos2f(GLfloat x, GLfloat y)
{
    glRasterPos3f(x,y,1.0f);
}

inline void glRasterPos2i(GLint x, GLint y)
{
    glRasterPos3f((GLfloat)x, (GLfloat)y, 1.0f );
}

inline void glRasterPos3fv(const GLfloat *v){
    glRasterPos3f(v[0],v[1],v[2]);
}

inline void glRasterPos2fv(const GLfloat *v){
    glRasterPos3f(v[0],v[1],1.0f);
}
#endif // HAVE_GLES

inline void glutBitmapString(void *font, const unsigned char *str)
{
#ifndef HAVE_GLES
    float g_raster_pos[4];
    glGetFloatv(GL_CURRENT_RASTER_POSITION, g_raster_pos);
#endif
    
    pangolin::GlFont::I().Text( (const char *)str ).DrawWindow(
        g_raster_pos[0], g_raster_pos[1], g_raster_pos[2]
    );
}

inline int glutBitmapLength(void *font, const unsigned char *str)
{
    return pangolin::GlFont::I().Text((const char *)str).Width();
}

#define GLUT_BITMAP_HELVETICA_12 0;

#endif // HAVE_GLUT
#endif // PANGOLIN_GLUT_BITMAP_H