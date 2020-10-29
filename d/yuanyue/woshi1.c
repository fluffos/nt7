inherit ROOM;
void create()
{
        set("short", "燕子坞"); 
        set("long", @LONG
这里是金狮的卧室。平常金狮倒算是豪爽，但一回到这里，便古
古怪怪的，大门紧闭，连窗户都会关上，银龙好几次想进来，都被金
狮轰了出去，弄得银龙好生没趣，一怒之下，趁金狮出门，在屋里还
算雪白的墙上留下了金狮的弥足珍贵的题词『燕子坞』。屋子里其实
除了张床外，什么也没有。银龙费尽心思，也没发现有什么不可告人
的地方。
LONG );
        set("type","indoors");
        set("exits",([
                "west":__DIR__"grass4",
                "south":__DIR__"grass3",
        ]) );

        set("item_desc", ([
                "墙": "墙上面龙飞凤舞写了几个大字：\n银龙到燕子坞一游，哈哈！可惜啥好玩的没有。\n",
                "wall": "墙上面龙飞凤舞写了几个大字：\n银龙到燕子坞一游，哈哈！可惜啥好玩的没有。\n",
        ]) ); 
        set("coor/x",-580);
        set("coor/y",250);
        set("coor/z",80);
        setup();
        replace_program(ROOM);
}    
