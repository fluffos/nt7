inherit ROOM; 

void create() 
{ 
        set("short", "天牢出口"); 
        set("long", @LONG 
这里黑沉沉的，即无一丝光亮，也无半分声息。黑暗中依稀可以
看到身边似乎有几个人影，看到你转过头去，他们立刻屏住呼吸，紧
张地瞪着你。四壁摸上去冰凉，且极硬，似乎都是钢铁铸成。脚边有
一堆东西踢上去克剌剌地散了开来，细看却是一具白得发亮的枯骨。
LONG
); 
                        
        set("outdoors", "necropolis"); 
        set("virtual_room", 1);
        set("no_magic", 1);
        set("exits", ([ /* sizeof() == 3 */ 
                "north":__DIR__"maze/exit",
                "out"  : "/d/city/wumiao",
        ])); 
                        
        setup();

} 
int valid_leave(object me, string dir)
{
        object *inv, obj;
        if (dir == "out")
        {
                tell_object(me, "check!\n");
                inv = all_inventory(me);
                if (inv && sizeof(inv)>0)
                        foreach(obj in inv) {
                                if( obj && query("maze_item", obj) )
                                        destruct(obj);
                        }
        }
        return 1;
}
