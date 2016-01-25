// Generated by gencpp from file rc_car/RSRMsg.msg
// DO NOT EDIT!


#ifndef RC_CAR_MESSAGE_RSRMSG_H
#define RC_CAR_MESSAGE_RSRMSG_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace rc_car
{
template <class ContainerAllocator>
struct RSRMsg_
{
  typedef RSRMsg_<ContainerAllocator> Type;

  RSRMsg_()
    : run(0)
    , reset(0)  {
    }
  RSRMsg_(const ContainerAllocator& _alloc)
    : run(0)
    , reset(0)  {
    }



   typedef int8_t _run_type;
  _run_type run;

   typedef int8_t _reset_type;
  _reset_type reset;




  typedef boost::shared_ptr< ::rc_car::RSRMsg_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::rc_car::RSRMsg_<ContainerAllocator> const> ConstPtr;

}; // struct RSRMsg_

typedef ::rc_car::RSRMsg_<std::allocator<void> > RSRMsg;

typedef boost::shared_ptr< ::rc_car::RSRMsg > RSRMsgPtr;
typedef boost::shared_ptr< ::rc_car::RSRMsg const> RSRMsgConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::rc_car::RSRMsg_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::rc_car::RSRMsg_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace rc_car

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'std_msgs': ['/opt/ros/indigo/share/std_msgs/cmake/../msg'], 'rc_car': ['/home/victorien/catkin_ws/src/rc_car/msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::rc_car::RSRMsg_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::rc_car::RSRMsg_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::rc_car::RSRMsg_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::rc_car::RSRMsg_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::rc_car::RSRMsg_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::rc_car::RSRMsg_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::rc_car::RSRMsg_<ContainerAllocator> >
{
  static const char* value()
  {
    return "8936b396549085d0c33078907663a46e";
  }

  static const char* value(const ::rc_car::RSRMsg_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x8936b396549085d0ULL;
  static const uint64_t static_value2 = 0xc33078907663a46eULL;
};

template<class ContainerAllocator>
struct DataType< ::rc_car::RSRMsg_<ContainerAllocator> >
{
  static const char* value()
  {
    return "rc_car/RSRMsg";
  }

  static const char* value(const ::rc_car::RSRMsg_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::rc_car::RSRMsg_<ContainerAllocator> >
{
  static const char* value()
  {
    return "int8 run\n\
int8 reset\n\
";
  }

  static const char* value(const ::rc_car::RSRMsg_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::rc_car::RSRMsg_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.run);
      stream.next(m.reset);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER;
  }; // struct RSRMsg_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::rc_car::RSRMsg_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::rc_car::RSRMsg_<ContainerAllocator>& v)
  {
    s << indent << "run: ";
    Printer<int8_t>::stream(s, indent + "  ", v.run);
    s << indent << "reset: ";
    Printer<int8_t>::stream(s, indent + "  ", v.reset);
  }
};

} // namespace message_operations
} // namespace ros

#endif // RC_CAR_MESSAGE_RSRMSG_H
