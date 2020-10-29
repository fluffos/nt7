#include <ansi.h>
inherit ROOM;
void create()
{
        set("short", "草坪");
        set("long",
"[1;32m这是一片碧绿的草坪，踩上去觉得异常的柔软温厚，草坪一\n"
"直延伸到小河畔，青青草根也浸入河水之中。河面上点点烁金,波纹乔崆\n"
"岬囱２萜旱哪厦妫豢酶叽蟮奈嗤┦鳎Ω尚鄙欤礁盘俅执滞炀鸵\n"
"桓銮锴?qiuqian)，一派乡土气息。你顿时被这里的美景迷住了，忘了萛n"
"プ纺侵恍【椤n"
);
        set("exits", ([ 
        ]) );

        set("item_desc", ([
        "qiu qian": "秋千系用古藤挽就，虽然简陋，却别有情趣。你可以试着荡荡(swing)看。\n",
        "tree": "高大的梧桐树把草坪的北方遮的严严实实。\n",
        ]) );
        
        set("no_magic", 1);
        setup();
}

void init()
{
   add_action("do_swing", "swing");
     add_action("do_north", "beifang"); 
   add_action("do_north", "n");
}

int do_north(string arg)
{
   object me;

   me = this_player(); 

 if( query_temp("marks/marble", me) )
   {
message_vision(HIW"$N绕过梧桐树，拨开草丛，忽然一阵狂风吹过，把$N吹了个踉跄。\n"NOR,me ); 
message_vision(HIW"风中传出一个声音：勇敢的人，谢谢你解开第一个封印，接着走下去吧。\n"NOR,me );
message("channel:chat",HBMAG"【精灵神界】"+query("name", me)+"成功解开第一个封印!\n"NOR,users());
      me->move(__DIR__"spirit5");
    set_temp("marks/marble", 0, me);
                set_temp("m_success/初级", 1, me);
   return 1;
   }
   else 
   tell_object(me, "那里没有出路。\n\n");
   return 1;
}

int do_swing(string arg )
{
        object me;
        me = this_player();

        if(!arg || arg != "秋千" && arg != "qiu qian" ) return 0;       
        switch (random (7)) {
                case 0:
message_vision(HIG"$N爬到秋千上，慢慢地开始荡起秋千，越荡越高。\n"NOR, me);
                break;
                case 1:
message_vision(HIG"秋千越荡越高，$N不由得紧紧抓住古藤。\n"NOR, me);
tell_object(me, "你只觉得风从脚底掠过，人似乎要乘风飞去。\n");
                break;
                case 2:
message_vision(HIG"秋千越荡越高，$N不由得紧紧抓住古藤。\n"NOR, me);
message("vision", me->name()+"似乎看到了什么东西，匆匆地从秋千上跳了下来。\n", environment(me), me);
  tell_object(me, "你忽然发现前面有什么发出耀眼的光，光一闪即失。似乎可以往北(beifang)。\n");
                set_temp("marks/marble", 1, me);
                break;
                case 3:
message_vision(HIR"秋千越荡越高，$N一不留神从秋千上掉了下来。\n"NOR, me);
tell_object(me, "＂砰！＂你重重地摔在树根上，屁股好痛哦！ \n");
                me->receive_damage("qi",25);   
                me->receive_damage("jing",20);   
                break;
                case 4:
message_vision(HIR"秋千越荡越高，$N一不留神从秋千上掉了下来。\n"NOR, me);
tell_object(me, "＂砰！＂你重重地摔在树根上，屁股好痛哦！ \n");
                me->receive_damage("qi",30);   
                me->receive_damage("jing",20);   
                break;
                case 5:
message_vision(HIR"秋千越荡越高，$N一不留神从秋千上掉了下来。\n"NOR, me);
tell_object(me, "＂砰！＂你重重地摔在树根上，屁股好痛哦！ \n");
                me->receive_damage("qi",50);   
                me->receive_damage("jing",20);   
                break; 
                case 6:
message_vision(HIR"秋千越荡越高，$N手一滑，从秋千上掉了下来。\n"NOR, me);
tell_object(me, "＂砰！＂你重重地摔在树根上，屁股好痛哦！ \n");
                me->receive_damage("qi",40);   
                me->receive_damage("jing",10);   
                break;        }
        return 1;
}
