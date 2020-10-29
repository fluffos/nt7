// 樵子 by leontt

inherit NPC;
inherit F_MASTER;
#include <ansi.h>

string axe();
string strike();
void create()
{
        set_name("樵子", ({ "qiao zi", "qiao", "zi" }) );
        set("gender", "男性" );
        set("age", 40);
        set("str", 30);
        set("con", 30);
        set("dex", 25);
        set("int", 25);
        set("per", 20);
        set("attitude", "friendly");

        set("max_qi", 5000);
        set("max_jing", 2800);
        set("eff_jingli", 3600);
        set("neili", 8000);
        set("qi", 5000);
        set("jingli", 3600);
        set("max_neili", 8000);
        set("jiali", 150);
        
        create_family("大理", 13, "弟子");
        set("chat_msg_combat", ({
                (: random_move :)
        }) );
        set("chat_chance", 15);
        set("chat_msg", ({
                (: random_move :)
        }) );

        set("long", 
        "此人左手提着一捆松柴，右手握着一柄斧子，看上去是一个樵夫。\n"+
        "只见他容色豪壮，神态虎虎，举手迈足间似是大将军有八面威风，\n"+
        "若非身穿粗布衣裳而在这山间樵柴，必当他是个叱诧风云的统兵 \n"+
        "元帅。\n");
        
        set("combat_exp", 2300000);
        set("score", 50000);
        set("startroom","/d/tiezhang/road-2"); 

        set("chat_chance_combat", 10);
        set("chat_msg_combat",({
         (: perform_action, "axe.jingtian" :),
         (: exert_function, "qi" :) 
        }));
           
        set_skill("parry", 280);
        set_skill("dodge", 280);
        set_skill("force", 280);
        set_skill("axe", 280);
        set_skill("literate", 200);
        set_skill("strike", 280);
        set_skill("qingyan-zhang", 280);
        set_skill("qiantian-yiyang", 280);
        set_skill("pangen-fu", 280);
        set_skill("tianlong-xiang", 280);
        set_skill("finger", 280);
        set_skill("yiyang-zhi", 280);
        set_skill("buddhism", 140);
        map_skill("dodge", "tianlong-xiang");
        map_skill("parry", "yiyang-zhi");
        map_skill("axe", "pangen-fu");
        map_skill("force", "qiantian-yiyang");
        map_skill("strike", "qingyan-zhang");
        map_skill("finger", "yiyang-zhi");
        prepare_skill("finger","yiyang-zhi");
        
        set("inquiry", ([
            "name": "你问这干什么? 你来这干什么？你和欧阳锋有什么关系？",
            "here": "你打死我也不会说的！",
            "基本斧法" : (: axe :),
            
        ]));

        set("chat_chance", 10);
        set("chat_msg", ({
"城池俱坏，英雄安在？云龙几度相交代？想兴衰，弱为怀。”\n",
"唐家才起隋家败，事态有如云变改。疾，也是天地差！迟，也是天地差！”\n",
"天津桥上，凭栏遥望，春陵王气都凋丧，树苍苍，水茫茫，云台不见中兴将，千古转头归灭亡。功，也不久长！名，也不久长！”\n",

        }) );
        
        carry_object("/clone/armor/b_cloth")->wear();
        carry_object("/clone/weapon/axe")->wield();
        
        setup();
}

string axe()
{
        mapping fam = this_player()->query("family");
        object ob;        
        if(!fam || fam["family_name"] != "天龙寺")
           return RANK_D->query_respect(this_player())+"与本派素无来往，不知此话从何谈起？";
        if(this_player()->query_skill("axe",1) > 100)
           return "你的斧法已经有一定基础了，这本书对你没什么用，还是留给别人吧";        
        ob = unew("/clone/book/axe-book");
        if(!clonep(ob))
           return "你来晚了，我的「基本斧法」已经给别人拿走了。";   
        if(clonep(ob) && ob->violate_unique()){
           destruct(ob);
           return "你来晚了，我的「基本斧法」已经给别人拿走了。";  
           }      
        ob->move(this_player());
           return "好吧，这本「基本斧法」就送给你了。";
}

void attempt_apprentice(object ob)
{     
        if( (string)ob->query("gender") == "女性" ){ 
                command ("say 我大理武功需要纯阳之体，小姑娘我可不收啊!");
                return;
        }
        if (ob->query("tls")){ 
                command ("say 你已经是天龙寺出家弟子了，我不能再收你了！\n");
                return;
        } 
        if( (int)ob->query_skill("qiantian-yiyang",1) < 150  ){      
                command ("hmm");
                command ("say 你乾天一阳功如此之差，我可不收你?");
                return;
        }
        if(ob->query_str() < 30){
                command("say 要学我的看家本领，必须臂力奇高，依我看" + RANK_D->query_respect(ob) + "的资质似乎不够？");
                return;
        }
        if ((int)ob->query("job_time/大理") < 300){
                command ("say 我看你为镇南王府做事做的还不够啊，努力做吧！");
                return;
        }      
        
        command("say 嗯，看你还是个学武的料，我就收下你吧！");
        command("giggle1");
        command("say 很好，" + RANK_D->query_respect(ob) + "多加努力，他日必定有成。");
        command("recruit " + ob->query("id") );
        ob->set("title","大理第十四代弟子");
}

int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
                add("apprentice_available", -1);
}

