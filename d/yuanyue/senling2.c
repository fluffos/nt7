// This program is a part of NITAN MudLIB

inherit ROOM;
void create()
{
        set("short", "松林"); 
        set("long", @LONG
这里是圆月山庄后园一片密密的松木林，四周一片寂静。松针落
的遍地都是，几乎把整个小路铺成了条软软的松毯，不知名的野兔偷
偷逃过，小路旁就是条静静流淌的小溪，溪水上漂浮着松针黄叶，荡
开枝叶，依稀可看到溪水碧绿如镜，清澈见底。拨开路旁一块石碑的
泥垢，隐约可以看到其上写着『沥泉』二字。
LONG );
        set("outdoors", "wansong");
        set("type","forest");
        set("exits",([
                "north":__DIR__"senling3",
                "southeast":__DIR__"senling1",
        ]) );
        set("item_desc", ([
                "brook": "溪水碧绿如镜，清澈见底，偶尔有几根松针漂浮在水面上。\n",
                "liquan": "溪水碧绿如镜，清澈见底，偶尔有几根松针漂浮在水面上。\n",
                "小溪": "溪水碧绿如镜，清澈见底，偶尔有几根松针漂浮在水面上。\n",
                "石碑": "石碑已经年代久远，破败不堪，但隐约可以看到上面刻着[沥泉]二字。\n",
                "stone": "石碑已经年代久远，破败不堪，但隐约可以看到上面刻着[沥泉]二字。\n",
                "shibei": "石碑已经年代久远，破败不堪，但隐约可以看到上面刻着[沥泉]二字。\n",
        ]) );
//      set("resource/water",1);
        set("liquid/name","泉水");
        set("liquid/type", "water");
        set("liquid/drunk_apply",0);
        set("coor/x",-620);
        set("coor/y",250);
        set("coor/z",80);
        setup();
        
}  
void init()
{
        add_action("do_fillwater", "fill");
} 
int do_fillwater(string arg)
{
        object *list, ob;
        int i, can_fillwater;
        string dir;
        function f; 
        if( !arg || arg=="" ) return 0; 
        if( arg=="skin" || arg=="wineskin" ) 
        {
                list = all_inventory(this_player());
                i = sizeof(list);
                can_fillwater = 0;
                for (i=0;i<sizeof(list);i++) 
                {
                  if( (query("liquid/type", list[i]) == "alcohol") || (query("liquid/type", list[i]) == "water") )
                  {
                        ob = list[i];
                        can_fillwater = 1;
                        ob->set("liquid",([
                                "type": "water",
                                "name": "沥泉水",
                                "remaining":query("max_liquid", ob),
                                "drunk_apply": 0,
                        ]) );
                        f = (: call_other, __FILE__, "drink_drug" :);
                        set("liquid/drink_func", bind(f,ob), ob);
                        write("你从小溪里装满了沥泉水！ \n");
                        return 1;
                   }
                }
                if (can_fillwater ==0) 
                {
                        write("你没有装水的东西啊....\n");
                        return 1;
                }
        }
        else 
        {
                write("你要往什么东西里灌水？\n");
        }
        return 1;
} 
int drink_drug(object ob)
{
        set_temp("fugui_liquan", 1, this_player());
        return 0;
} 
