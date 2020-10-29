// This program is a part of NITAN MudLIB 
// redl 2012/12/1 
#include <ansi.h>

inherit NPC;

int ask_pan()
{
    object me = this_player();
    
                if ( time() - query("lgt/askpan", me) < 60 ){
                        tell_object(me, CYN"杨小邪怪眼一睨对你邪笑道：才问过又要来问，存心找削是不？\n"NOR); 
                        return -1; 
                }
    
    command("look " + query("id", me));
    command("whisper " + query("id", me) + " about 现在闯灵感塔需要有" + chinese_number(environment(this_object())->total_gold()) + "黄金的存款作为保证！");
    command("heihei " + query("id", me));
    set("lgt/askpan", time(), me);
    
        return 1;
}

void create()
{
        set_name(NOR "杨小邪" NOR, ({ "yang xiaoxie","yang","npc_yangxiaoxie" }) );
        set("title", NOR "通吃帮帮主" NOR);
        set("nickname", MAG "浪子不归.飞刀无痕.邪功天下第一" NOR);
        set("gender", "男性");
        set("age", 17);
        set("long", NOR"他就是江湖上赫赫有名的通吃帮帮主通吃小霸王，看起来很是邪恶的样子。\n"NOR);
        set("attitude", "peaceful");
        set("str", 30);
        set("con", 30);
        set("int", 30);
        set("dex", 30);
        set("per", 25);

        set("chat_chance", 1);
        set("chat_msg", ({
                                (: command("xixi npc_xiaoding") :),
                                (: command("grin npc_xiaoding") :),
                                (: command("ruffle npc_xiaoding") :),
        }) );

                set("level", 60);
        set("combat_exp", 10000000);

        set("inquiry", ([
                "盘口"   : (: ask_pan :),
                "灵感塔"     : "没意思，我刚从上面跳下来，你也想登上去吗？那得和我赌一把。\n"+NOR,
                "怎么赌"     : "我和每个成功登塔的高手签约，你如果失败了得付我们若干黄金，只要你钱庄里有存款。\n"+NOR,
                "签约"     : "你想做歌星？唉，有足够的存款直接上去就行了，你输了我自己去取。\n"+NOR,
                "小丁"     : "不就在我旁边吗..你都知道了？呃，是的，其实我们都不够邪恶...\n"+NOR,
        ]));

        setup();

}




