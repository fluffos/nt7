// This program is a part of NITAN MudLIB

inherit ROOM;

void create()
{
        set("short", "芳草坪"); 
        set("long", @LONG
这里是一块芳草坪，绿草茵茵，蝴蝶漫舞，花香扑鼻，让人感到
十分惬意。不禁令人就想一头躺倒上去，好好的去睡一觉，但这里偶
尔也会碰到菜花蛇。东面是片小树林，向北是间卧室。
LONG );
        set("type","grassland");
        set("outdoors", "wansong");
        set("exits",([
                "west":__DIR__"grass2",
                "north":__DIR__"woshi1",
                "southwest":__DIR__"shibanlu4",
        ]) );
        set("objects",([
                "/clone/beast/caihuashe" : 1,
                __DIR__"obj/grass" : 1,
        ]) ); 
        set("coor/x",-580);
        set("coor/y",240);
        set("coor/z",80);
        setup();
} 
void init()
{
        add_action("do_search", "search");
} 
int do_search(string arg)
{
        object me,obj;
        object grass;
        me = this_player();
        grass = present("grass", this_object()); 
        if(!arg) 
        {
                write("你要在哪里找东西？给点提示好不好，老大！\n");
                return 1;
   }
        
        if( me->is_busy() )
                return notify_fail("你上一个动作还没有完成，不能查找。\n");
        
        if( arg == "grass" || arg == "绿草"  )
        {
                if ( !query("gotit") && ! random(5) )
                {
                        message_vision("$N蹲下身子，仔细的找了起来，发现有点东西藏在绿草下边。\n",me);
                        obj = new("/clone/beast/caihuashe");
                        obj->move(grass);
                        set("gotit",1);
                }
                else
                {
                        message_vision("$N用手拨开草丛，仔细的查找一番，但什么都没有找到。\n",me);
                        me->start_busy(2);
                }
        }
        else
        {
                write("你找不到"+arg+"。\n");
                return 1;
        }
        return 1;
} 
void reset()
{
        ::reset();
        if( query("gotit") ) set("gotit",0);
}      
