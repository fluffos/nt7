// This program is a part of NITAN MudLIB

inherit ROOM;

void create()
{
        set("short", "白梅园"); 
        set("long", @LONG
这里便是白梅园了，平常金狮就最喜欢到这里走走，说是在清雅
的梅香中能静下心想些事情，每逢此时，银龙定会撇撇下嘴，不屑道：
一个人的身上穿的若还是春天的薄衣服，肚子里装的若还是昨天吃的
阳春面，他唯一还有心情欣赏的东西就是可以往嘴里吞下去、塞饱肚
子的，决不会是什么梅花。当然梅花若是换成辣椒那倒可以考虑考虑。
秋天的梅树上没什么花，但奇怪的是这里仍飘散着一股清香。
LONG );
        set("type","forest");
        set("outdoors", "wansong");
        set("exits",([
                "east":__DIR__"woshi1",
                "west":__DIR__"woshi",
                "north":__DIR__"chaifang",
        ]) );
        set("item_desc", ([
                "梅树": "梅树上没有花，树干上钉了一块小牌子，年代看来很久远了。\n",
                "tree": "梅树上没有花，树干上钉了一块小牌子，年代看来很久远了。\n",
                "牌子": "牌子上写着-[..动埋....处。]，但是年代久远，有几个字看不清了。\n",
                "paizi": "牌子上写着-[..动埋....处。]，但是年代久远，有几个字看不清了。\n"
        ]) );
        set("objects",([
                CLASS_D("mojiao/jinshi") : 1,
        ]) );
        
        set("coor/x",-590);
        set("coor/y",250);
        set("coor/z",80);
        setup();
} 

int dig_notify(object obj, int i)
{
        object me,jt;
        int qi;
        int max_qi;
        me = this_player();
        
        qi=query("qi", me);
        max_qi=query("max_qi", me);
        if (qi < max_qi/4) {
                message_vision("$N抡手中的"+obj->name()+"，但是脑中突然一阵眩晕......\n" , me);
           me->unconcious();
        }
        else {
                message_vision("$N手中的"+obj->name()+"碰到坚硬的地面，发出＇叮＇的一声。\n" , me);
                me->receive_damage("qi",query("max_qi", me)/4);
                if (query("digged")) 
                {
                        message_vision("$N辛辛苦苦挖了半天什么也没挖到。\n", me);
                        return 1;
                }
                else
                {
                        switch ( random(3) )
                        {
                          case 0: 
                                message_vision("$N发现地下似乎有个酒坛子。\n",this_player());
                                jt = new(__DIR__"obj/bottle");
                                jt->move(this_player());
                                set("digged",1);
                                message_vision("$N激动地扔掉"+obj->name()+"，连忙捡起"+jt->name()+"。 \n",this_player());
                                destruct(obj);
                                break;
                          case 1:
                                message_vision("地上的土被$N翻起一块,没什么发现。\n",obj);
                                break;
                          case 2:
                                message_vision("锵．．得一声，$N手中的"+obj->name()+"断了。\n",this_player());
                                destruct(obj);
                                break;
                        }
                 }
                 me->start_busy(3);
         }
         return 1; 
}    
