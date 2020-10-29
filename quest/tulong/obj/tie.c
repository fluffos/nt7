inherit ITEM;
mapping where_map=([
"gc":"/d/city/guangchang",
"sl":"/d/shaolin/guangchang1",
"bt":"/d/baituo/dating",
"tam":"/d/city2/tian_anm",
"hmy":"/d/heimuya/up1",
"hs":"/d/huashan/zhenyue",
"wd":"/d/wudang/chaotiangong",
"ts":"/d/taishan/nantian",
"xy":"/d/xiaoyao/qingcaop",
"xx":"/d/xingxiu/xxh1",
"xs":"/d/xueshan/dadian",
"shl":"/d/shenlong/dating",
"qz":"/d/quanzhou/zhongxin",
"lj":"/d/lingjiu/dating",
]);
void init(){
add_action("do_trans","trans");
}
void create(){
set_name("魔法传送帖",({"trans site","site"}));
set_weight(100); set_max_encumbrance(8000);
set("no_drop", "这样东西不能离开你。\n");
        if( clonep() )                set_default_object(__FILE__);
 else {     set("long",              "一张魔法传送帖，以它的魔力现在所能到达(trans)的地方如下。\n
\t中央广场(gc)    少林寺(sl)  白驼山(bt)  天安门(tam) \n
\t黑木崖(hmy)     华山(hs)    武当山(wd)  泰山(ts)    \n
\t逍遥派(xy)      星宿海(xx)  雪山寺(xs)  神龙教(shl) \n
\t泉州(qz)        灵鹫宫(lj)\n");
set("unit","张"); 
set("use_count", 6);}
}
int do_trans(string arg){
        object me,obj;string msg,str;str=where_map[arg];
        if( !arg||!stringp(str)) return notify_fail("你要去哪里？\n");
me=this_player();
             if( !query("outdoors", environment(me)) )
 return notify_fail("在这房间里无法使用魔法传送。\n");
 if (me->is_fighting())
return notify_fail("战斗中无法使用魔法传送！");
str+=".c";
        if(file_size(str)<0) 
return notify_fail("没有这个地方。\n");
        if (query("use_count") < 1) 
            {
message_vision("魔法传送帖闪出一道金光，随后便消失了。\n",me); 
          destruct(this_object());
          return 1;            }
    if( stringp(msg=query("env/msg_mout", me))){if( msg != "")message_vision(msg+"\n",me);}
       else                message_vision("只见一阵烟雾过後，$N的身影已经不见了。\n", me);
me->move(str); 
addn("use_count",-1);if( stringp(msg=query("env/msg_min", me)) )
       {if (msg!="") message_vision(msg+"\n", me);}
        else                message_vision("$N的身影突然出现在一阵烟雾之中。\n", me);        return 1;}