inherit ROOM; 

void create() 
{ 
        set("short", "天牢入口"); 
        set("long", @LONG 
这里黑沉沉的，即无一丝光亮，也无半分声息。黑暗中依稀可以
看到身边似乎有几个人影，看到你转过头去，他们立刻屏住呼吸，紧
张地瞪着你。四壁摸上去冰凉，且极硬，似乎都是钢铁铸成，只有南
北面各有一道小门，门上开了个巴掌大的洞，象是送饭用的。脚边有
一堆东西踢上去克剌剌地散了开来，细看却是一具白得发亮的枯骨。
LONG
); 
                        
        set("outdoors", "prison"); 
        set("virtual_room", 1);
        set("no_death", 1);
        set("no_magic", 1);
        set("exits", ([ /* sizeof() == 3 */ 
                "south" : __DIR__"maze/entry", 
        ])); 
        setup();
 
} 

