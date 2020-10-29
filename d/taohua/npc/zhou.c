// zhou.c 周伯通
#include <ansi.h>
inherit NPC;
int jie_bai();
void create()
{
        set_name("周伯通", ({ "zhou botong", "zhou", "bo tong" }));
        set("gender", "男性");
        set("nickname", CYN "老顽童" NOR ) ;
        set("age", 45);
        set("long",
        "他就是人称「老顽童」的周伯通。\n"
        "他本来是全真教掌门人的师弟，武功高强，但现在却被人囚禁在\n"
        "这小小山洞之中，头发胡子长长的，毛茸茸的象一个野人。\n",
        );
        set("combat_exp", 64000000);
        set("shen", 10000);
        set("max_neili", 3000);
        set("neili", 500000);
        set_skill("force", 250);
        set_skill("sword", 250);
        set_skill("unarmed", 250);
        set_skill("dodge", 250);
        set_skill("parry", 250);
        set_skill("zuoyou-hubo" ,1100);
        set_skill("kongming-quan",250);
        map_skill("unarmed","kongming-quan");
        map_skill("parry","kongming-quan");
        set("inquiry", ([
                "九阴真经" : "「九阴真经」就在我床上，你有本事杀了我\n"
                              " 或把我逼出山洞就可以取走！\n",
                "黄药师" : "他囚了我十五年，总想把我逼出山洞"
                           "以取「九阴真经」，\n可他每次来都是扫兴而归！\n",
                "瑛姑" :   "我、我、、我不认识她！",
                "蛇" :     "不要吓我，我最怕蛇了！\n",
                "结拜" :   (: jie_bai :),
        ]) );
        create_family("全真教", 11, "弟子");
        set_temp("apply/attack", 50);
        set_temp("apply/defense", 50);
        set_temp("apply/damage", 15);
        setup();
        carry_object("/clone/cloth/cloth")->wear();
}
int jie_bai()
{
        object ob ;
        ob = this_player ( ) ;
        if( query("gender", ob) != "男性" )
        {
                message_vision("\n老顽童上上下下打量了$N一番，说到：我生平不喜同两种人\n"
                "打交道：一是女人，二是太监。我看你还是趁早请罢！”\n", ob);
                return 1;
        }
      if( query("character", ob) == "心狠手辣" || query("character", ob) == "阴险奸诈" )
  {
              say("老顽童哼了一声说：就凭你这种恶人也配与我称兄道弟？！\n");
              return 1;
      }
        if( query("shen", ob)<-1000 )
        {
                say("老顽童哼了一声说：就凭你这种恶人也配与我称兄道弟？！\n");
                return 1;
        }
        say("老顽童高兴地说：好！以后我们就是好兄弟了！\n");
        tell_object(ob,GRN "周伯通悄悄对你说：老哥哥有一套「双手互搏之术」和一路\n"
        "「空明拳」可以传给你作为见面礼哟！\n" NOR );
        set_temp("wantong/兄弟", 1, this_player());
        return 1;
}
int recognize_apprentice(object ob, string skill)
{
        if( !query_temp("wantong/兄弟", ob) )
                return 0; 

        if (skill != "kongming-quan" && skill != "zuoyou-hubo")
                return 0; 
        return 1;
}
int accept_object(object who, object ob)
{    
        if ( (string)ob->name() == "毒蛇")
        {
                message_vision("$N拿出一条毒蛇在老顽童的眼前晃了晃．．．．．．\n"
                "老顽童吓得跳了起来，冲出洞外！边跑边喊：咬死了，咬死了！\n\n\n"
                "声音渐渐远去，终于不复耳闻。\n" ,who);
            call_out("dest",1,this_object());
                return 0;
        }
        return 0;
}
void dest(object me)
{
    if (me)  destruct(me);
}
