inherit ROOM;
/*
string go_enter(object me)
{
        if( query_temp("been_recommend_to_yaowang", me )
         || (query("family/family_name", me) == "药王谷") )
                return __DIR__"gd2";
        else
                return __DIR__"gd1";
}
//不知道为什么不能用这类语句。
string go_out(object me)
{
        if( query("family/family_name", me) == "药王谷" )
                return __DIR__"gd1";
        else
                return __DIR__"shulin/exit";
}
*/
void create()
{
        set("short", "独木桥");
        set("long", @LONG
这是一座原木绑成的小桥，人走在上面吱吱嘎嘎的乱响，好
像随时都会倒塌，让人提心吊胆。
LONG
        );
        set("exits", ([ /* sizeof() == 2 */
  "north" : __DIR__"gd2",
  "south" : __DIR__"gd1",
]));

        set("outdoors", "yaowang");
        setup();
}
