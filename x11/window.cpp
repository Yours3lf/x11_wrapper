#include "window.h"

#include "atom.h"
#include "screen.h"

#include <X11/Xlib.h>

namespace x11
{
  unsigned int window::input_only = InputOnly;
  unsigned int window::input_output = InputOutput;
  int window::copy_from_parent = CopyFromParent;
  int window::raise_lowest = RaiseLowest;
  int window::lower_highest = LowerHighest;
  int window::prop_mode_replace = PropModeReplace;
  int window::prop_mode_prepend = PropModePrepend;
  int window::prop_mode_append = PropModeAppend;
  int window::is_unmapped = IsUnmapped;
  int window::is_unviewable = IsUnviewable;
  int window::is_viewable = IsViewable;

  void window::create_window( display d, window parent, int x, int y, unsigned int width, unsigned int height, unsigned int border_width, int depth, unsigned int win_class, void* visual, long unsigned int valuemask, void* attributes )
  {
    data = XCreateWindow( static_cast<Display*>( d.get() ), parent.data, x, y, width, height, border_width, depth, win_class, static_cast<Visual*>( visual ), valuemask, static_cast<XSetWindowAttributes*>( attributes ) );
  }

  void window::create_simple_window( display d, window parent, int x, int y, unsigned int width, unsigned int height, unsigned int border_width, long unsigned int border, long unsigned int background )
  {
    data = XCreateSimpleWindow( static_cast<Display*>( d.get() ), parent.data, x, y, width, height, border_width, border, background );
  }

  void window::destroy_window( display d )
  {
    XDestroyWindow( static_cast<Display*>( d.get() ), data );
  }

  void window::destroy_subwindows( display d )
  {
    XDestroySubwindows( static_cast<Display*>( d.get() ), data );
  }

  void window::map_window( display d )
  {
    XMapWindow( static_cast<Display*>( d.get() ), data );
  }

  void window::map_raised( display d )
  {
    XMapRaised( static_cast<Display*>( d.get() ), data );
  }

  void window::map_subwindows( display d )
  {
    XMapSubwindows( static_cast<Display*>( d.get() ), data );
  }

  void window::unmap_window( display d )
  {
    XUnmapWindow( static_cast<Display*>( d.get() ), data );
  }

  void window::unmap_subwindows( display d )
  {
    XUnmapSubwindows( static_cast<Display*>( d.get() ), data );
  }

  void window::withdraw_window( display d, int screen_num )
  {
    XWithdrawWindow( static_cast<Display*>( d.get() ), data, screen_num );
  }

  void window::configure_window( display d, unsigned int value_mask, void* values )
  {
    XConfigureWindow( static_cast<Display*>( d.get() ), data, value_mask, static_cast<XWindowChanges*>( values ) );
  }

  void window::move_window( display d, int x, int y )
  {
    XMoveWindow( static_cast<Display*>( d.get() ), data, x, y );
  }

  void window::resize_window( display d, unsigned int width, unsigned int height )
  {
    XResizeWindow( static_cast<Display*>( d.get() ), data, width, height );
  }

  void window::move_resize_window( display d, int x, int y, unsigned int width, unsigned int height )
  {
    XMoveResizeWindow( static_cast<Display*>( d.get() ), data, x, y, width, height );
  }

  void window::set_window_border_width( display d, unsigned int width )
  {
    XSetWindowBorderWidth( static_cast<Display*>( d.get() ), data, width );
  }

  void window::raise_window( display d )
  {
    XRaiseWindow( static_cast<Display*>( d.get() ), data );
  }

  void window::lower_window( display d )
  {
    XLowerWindow( static_cast<Display*>( d.get() ), data );
  }

  void window::circulate_subwindows( display d, int direction )
  {
    XCirculateSubwindows( static_cast<Display*>( d.get() ), data, direction );
  }

  void window::circulate_subwindows_up( display d )
  {
    XCirculateSubwindowsUp( static_cast<Display*>( d.get() ), data );
  }

  void window::circulate_subwindows_down( display d )
  {
    XCirculateSubwindowsDown( static_cast<Display*>( d.get() ), data );
  }

  void window::restack_windows( display d, const std::vector< window >& windows )
  {
    XRestackWindows( static_cast<Display*>( d.get() ), ( Window* )&windows[0], windows.size() );
  }

  void window::change_window_attributes( display d, long unsigned int valuemask, void* attributes )
  {
    XChangeWindowAttributes( static_cast<Display*>( d.get() ), data, valuemask, static_cast<XSetWindowAttributes*>( attributes ) );
  }

  void window::set_window_background( display d, long unsigned int background_pixel )
  {
    XSetWindowBackground( static_cast<Display*>( d.get() ), data, background_pixel );
  }

  void window::set_window_background_pixmap( display d, long unsigned int pixmap )
  {
    XSetWindowBackgroundPixmap( static_cast<Display*>( d.get() ), data, pixmap );
  }

  void window::set_window_border( display d, long unsigned int border_pixel )
  {
    XSetWindowBorder( static_cast<Display*>( d.get() ), data, border_pixel );
  }

  void window::set_window_border_pixmap( display d, long unsigned int border_pixmap )
  {
    XSetWindowBorderPixmap( static_cast<Display*>( d.get() ), data, border_pixmap );
  }

  void window::set_window_colormap( display d, long unsigned int colormap )
  {
    XSetWindowColormap( static_cast<Display*>( d.get() ), data, colormap );
  }

  void window::define_cursor( display d, long unsigned int cursor )
  {
    XDefineCursor( static_cast<Display*>( d.get() ), data, cursor );
  }

  void window::undefine_cursor( display d )
  {
    XUndefineCursor( static_cast<Display*>( d.get() ), data );
  }

  bool window::query_tree( display d, window& root, window& parent, std::vector< window >& children )
  {
    Window r;
    Window p;
    Window* ch = 0;
    unsigned int numc = 0;
    int ret = XQueryTree( static_cast<Display*>( d.get() ), data, &r, &p, &ch, &numc );
    root = r;
    parent = p;

    for( int c = 0; c < numc; ++c )
      children.push_back( ch[c] );

    XFree( ch );
    return ret;
  }

  bool window::get_window_attributes( display d, window_attributes& attributes )
  {
    XWindowAttributes wa;
    bool ret = XGetWindowAttributes( static_cast<Display*>( d.get() ), data, &wa );

    if( ret )
    {
      attributes = window_attributes( wa.x, wa.y, wa.width, wa.height,
                                      wa.border_width, wa.depth, wa.visual, wa.root, wa.c_class, wa.bit_gravity, wa.win_gravity,
                                      wa.backing_store, wa.backing_planes, wa.backing_pixel, wa.save_under, wa.colormap,
                                      wa.map_installed, wa.map_state, wa.all_event_masks, wa.your_event_mask, wa.do_not_propagate_mask,
                                      wa.override_redirect, wa.screen );
    }

    return ret;
  }

  bool window::get_geometry( display d, long unsigned int drawable, window& root, int& x, int& y, unsigned int& width, unsigned int& height, unsigned int& border_width, unsigned int& depth )
  {
    Window roott;
    int xx, yy;
    unsigned int widtht, heightt, border_widtht, deptht;
    int ret = XGetGeometry( static_cast<Display*>( d.get() ), drawable, &roott, &xx, &yy, &widtht, &heightt, &border_widtht, &deptht );
    root = roott;
    x = xx;
    y = yy;
    width = widtht;
    height = heightt;
    border_width = border_widtht;
    depth = deptht;
    return ret;
  }

  bool window::translate_coordinates( display d, window src, window dst, int src_x, int src_y, int& dst_x, int& dst_y, window& child )
  {
    int dest_x, dest_y;
    Window childt;
    int ret = XTranslateCoordinates( static_cast<Display*>( d.get() ), src.data, dst.data, src_x, src_y, &dest_x, &dest_y, &childt );
    dst_x = dest_x;
    dst_y = dest_y;
    child = childt;
    return ret;
  }

  bool window::query_pointer( display d, window& root, window& child, int& root_x, int& root_y, int& win_x, int& win_y, unsigned int& mask )
  {
    Window roott, childrent;
    int root_xt, root_yt, win_xt, win_yt;
    unsigned int maskt;
    int ret = XQueryPointer( static_cast<Display*>( d.get() ), data, &roott, &childrent, &root_xt, &root_yt, &win_xt, &win_yt, &maskt );
    root = roott;
    child = childrent;
    root_x = root_xt;
    root_y = root_yt;
    win_x = win_xt;
    win_y = win_yt;
    mask = maskt;
    return ret;
  }

  template< class t, int length >
  bool get_window_property( display d, window w, unsigned long prop_length, atom property_name, Atom property_type, long prop_offset, std::vector<t>& property )
  {
    Atom actual_type;
    int actual_format;
    unsigned long nitems, bytes_left_to_read;
    unsigned char* propertyarray;
    int ret = XGetWindowProperty( static_cast<Display*>( d.get() ), w.get(), property_name.get(), prop_offset, prop_length, false, property_type, &actual_type, &actual_format, &nitems, &bytes_left_to_read, &propertyarray );

    if( ret != Success )
    {
      XFree( propertyarray );
      return false;
    }

    if( actual_type == None )
    {
      //property does not exist
      XFree( propertyarray );
      return false;
    }

    if( actual_format != length )
    {
      //format does not match the supplied array
      XFree( propertyarray );
      return false;
    }

    for( int c = 0; c < nitems; ++c )
    {
      property.push_back( ( ( t* )( propertyarray + 4 * prop_offset ) )[c] );
    }

    XFree( propertyarray );

    if( bytes_left_to_read > 0 )
    {
      //need to read some more
      return get_window_property<t, length>( d, w, bytes_left_to_read, property_name, actual_type, prop_offset, property );
    }

    return true;
  }

  bool window::get_window_property_char( display d, atom property_name, long int prop_offset, std::vector< char >& property )
  {
    return get_window_property<char, 8>( d, *this, 0, property_name, AnyPropertyType, prop_offset, property );
  }

  bool window::get_window_property_short( display d, atom property_name, long int prop_offset, std::vector< short int >& property )
  {
    return get_window_property<short, 16>( d, *this, 0, property_name, AnyPropertyType, prop_offset, property );
  }

  bool window::get_window_property_long( display d, atom property_name, long int prop_offset, std::vector< long int >& property )
  {
    return get_window_property<long, 32>( d, *this, 0, property_name, AnyPropertyType, prop_offset, property );
  }

  template< class t, int length >
  void change_property_helper( display d, window w, atom property, atom type, int mode, const std::vector<t>& data )
  {
    XChangeProperty( static_cast<Display*>( d.get() ), w.get(), property.get(), type.get(), length, mode, ( unsigned char* )&data[0], data.size() );
  }

  void window::change_property_char( display d, atom property, atom type, int mode, const std::vector< char >& data )
  {
    change_property_helper<char, 8>( d, *this, property, type, mode, data );
  }

  void window::change_property_short( display d, atom property, atom type, int mode, const std::vector< short int >& data )
  {
    change_property_helper<short, 16>( d, *this, property, type, mode, data );
  }

  void window::change_property_long( display d, atom property, atom type, int mode, const std::vector< long int >& data )
  {
    change_property_helper<long, 32>( d, *this, property, type, mode, data );
  }

  void window::list_properties( display d, std::vector< atom >& atoms )
  {
    int num;
    Atom* atomst = XListProperties( static_cast<Display*>( d.get() ), data, &num );

    for( int c = 0; c < num; ++c )
      atoms.push_back( atomst[c] );

    XFree( atomst );
  }

  void window::rotate_window_properties( display d, const std::vector< atom >& atoms, int npositions )
  {
    XRotateWindowProperties( static_cast<Display*>( d.get() ), data, ( Atom* )&atoms[0], atoms.size(), npositions );
  }

  void window::delete_property( display d, atom property )
  {
    XDeleteProperty( static_cast<Display*>( d.get() ), data, property.get() );
  }

  window window::get_selection_owner( display d, atom selection )
  {
    return XGetSelectionOwner( static_cast<Display*>( d.get() ), selection.get() );
  }

  void window::convert_selection( display d, atom selection, atom target, atom property, long unsigned int time )
  {
    XConvertSelection( static_cast<Display*>( d.get() ), selection.get(), target.get(), property.get(), data, time );
  }

  void window::set_selection_owner( display d, atom selection, long unsigned int time )
  {
    XSetSelectionOwner( static_cast<Display*>( d.get() ), selection.get(), data, time );
  }

  template< int fmt >
  bool send_event( display d, unsigned long data, unsigned long target, atom type, bool propagate, long int data0, long int data1, long int data2, long int data3, long int data4 )
  {
    XEvent ev = {0};
    ev.xclient.type = ClientMessage;
    ev.xclient.window = data;
    ev.xclient.message_type = type.get();
    ev.xclient.send_event = True;
    ev.xclient.format = fmt;
    ev.xclient.data.l[0] = data0;
    ev.xclient.data.l[1] = data1;
    ev.xclient.data.l[2] = data2;
    ev.xclient.data.l[3] = data3;
    ev.xclient.data.l[4] = data4;

    bool ret = XSendEvent( static_cast<Display*>( d.get() ), target, false, NoEventMask, &ev ) == Success;
    d.sync();

    return ret;
  }

  bool window::send_event_char( display d, window target, atom type, bool propagate, long int data0, long int data1, long int data2, long int data3, long int data4 )
  {
    return send_event<8>( d, data, target.data, type, propagate, data0, data1, data2, data3, data4 );
  }

  bool window::send_event_short( display d, window target, atom type, bool propagate, long int data0, long int data1, long int data2, long int data3, long int data4 )
  {
    return send_event<16>( d, data, target.data, type, propagate, data0, data1, data2, data3, data4 );
  }

  bool window::send_event_long( display d, window target, atom type, bool propagate, long int data0, long int data1, long int data2, long int data3, long int data4 )
  {
    return send_event<32>( d, data, target.data, type, propagate, data0, data1, data2, data3, data4 );
  }
}
