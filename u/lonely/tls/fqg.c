inherit ROOM;

void create()
{
  set("short","飞泉沟");
  set("long",@LONG
这里已是天龙寺的后山很偏僻的地方了，一道瀑布从天而降，空
气里充满了瀑布溅起的水雾，在阳光直射下，幻出一道道七色彩虹，
瀑布顺着山沟流向南面的百丈桥，路边大石林立，古树参天。
LONG);
     set("outdoors", "天龙寺");
     set("exits",([
           "northup" : __DIR__"wxt",
           "south" : __DIR__"bzqn",
               ]));

     set("coor/x",-390);
  set("coor/y",-260);
   set("coor/z",30);
   setup();
}