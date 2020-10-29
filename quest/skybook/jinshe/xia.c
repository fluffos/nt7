// This program is a part of NT MudLIB
//增加金蛇解密第二阶段

#include <ansi.h>;
inherit NPC;
#define QUESTDIR "quest/金蛇剑法/"
int ask_weapon();
int ask_fuchou();
int ask_jinshe();
int ask_anqi();

void throwing();
int do_kill(object me, object dest);
int give_weapon();
void create()
{
        set_name("夏雪宜", ({ "xia xueyi", "xia", "xueyi" }) );
        set("nickname", HIY"金蛇郎君"NOR);
        set("gender", "男性" );
        set("shen_type", 1);
        set("age", 23);
        set("str", 34);
        set("con", 28);
        set("int", 27);
        set("dex", 34);
        set("per", 30);
        set("location", 1);
        set("shen", -50000);
        set("long",@LONG
这人身材高挑，相貌出众。他幼时全家不幸被温家五
老劫掠灭门，立志报仇。此人性情古怪，为人阴狠，
武功便正如其人般诡异难测。江湖上人人闻其名而为
之色变，乃是出名的难缠人物。
LONG);
        set("combat_exp", 2500000);
        set("attitude", "heroism");
        set("max_qi", 6000);
        set("quest/金蛇剑法/pass", 1);
        set("unique", 1);
        set("max_jing", 5000);
        set("eff_jingli", 3000);
        set("neili", 10000);
        set("max_neili", 10000);
        set("jiali", 70);
        set_skill("force", 260);
        set_skill("medicine", 130);
        set_skill("hunyuan-yiqi", 260);
        set_skill("literate", 200);
        set_skill("jinshe-jianfa", 260);
        set_skill("jinshe-zhangfa", 260);
        set_skill("sword", 260);
        set_skill("dodge", 260);
        set_skill("parry", 260);
        set_skill("strike", 260);
        set_skill("xinyuegong", 260);

        set("chat_chance_combat", 30);
        set("chat_msg_combat", ({
                (: perform_action, "sword.kuangwu" :),
                (: perform_action, "sword.sheying" :),
                (: throwing :),
        }));
        set("chat_chance", 35);
        set("chat_msg", ({ (: random_move :), }));

    set("inquiry", ([
            "金蛇锥" : (: ask_weapon :),
            "报仇" : (: ask_fuchou :),
            "暗器" : (: ask_anqi :),
            "复仇" : (: ask_fuchou :),
             "心得" : (: ask_jinshe :),
            "金蛇剑法" : (: ask_jinshe :),
             "秘诀" : (: ask_jinshe :),
                ]));
 
        map_skill("force", "hunyuan-yiqi");
        map_skill("strike", "jinshe-zhangfa");
        map_skill("dodge", "xinyuegong");
        map_skill("parry", "jinshe-zhangfa");
        map_skill("sword", "jinshe-jianfa");
        prepare_skill("strike", "jinshe-zhangfa");

        set_temp("apply/armor", 60);
        set_temp("apply/dodge", 60);
        set_temp("apply/damage", 70);
        set_temp("apply/attack", 80);
        setup();

        if (clonep()) {
                UPDATE_D->get_cloth(this_object());
                add_money("gold", 2);
           carry_object("/d/huashan/jinshe/obj/jinshe-zhui");
                give_weapon();
                call_out("do_back", 300+random(200), this_object());
        }
}

int give_weapon()
{
        object sword, weapon;
        if (clonep(this_object())) {
                if( !objectp(weapon=query_temp("weapon", this_object()))){
                        sword = unew(BINGQI_D("sword/jinshesword"));
                        if(!sword) sword = unew(BINGQI_D("changjian1"));
                        sword->move(this_object());
                        sword->wield();
                }
                else if( query("id", weapon) != "jinshesword" && 
                        objectp(sword = unew(BINGQI_D("sword/jinshesword")))) {
                                weapon->unequip();
                                destruct(weapon);
                                sword->move(this_object());
                                sword->wield();
                }

                if(objectp(sword = unew(BINGQI_D("throwing/jinshe-zhui"))) )
                        sword->move(this_object());
                if(!objectp(sword = present("zhuihun biao", this_object()))
                || sword->query_amount() < 2 )
                        carry_object(BINGQI_D("zh_biao"));
        }
}

void init()
{
        object ob, me;
        me = this_object();
        ::init();
        if (interactive(ob = this_player()) && !wizardp(ob) && !is_fighting()){
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
        add_action("do_look",({"look", "consider", "smash", "kick", "kick2", "cut", "flirt", "lean"
                                "love", "interest", "kiss" }));
}


int do_look(string target)
{
        object me;

        if( !target ) return 0;
        me = this_player();

        if( id(target) && query("gender", me) != "女性" && !is_busy() && !wizardp(me)){
                message("vision",HIR "夏雪宜鹰眼一挑：讨厌的"+RANK_D->query_rude(me)+"，滚！！\n"NOR, environment(), this_object() );
                if(present("zhuihun biao", me))
                        command("throwbiaoat"+query("id", me));
                else COMBAT_D->do_attack(this_object(),me,query_temp("weapon", this_object()),1);
        }
        return 0;
}

void greeting(object ob)
{
        object me = this_object();

        if(!me || !ob || environment(ob) != environment(this_object())) return;

        if( query("combat_exp", ob)>800000 && query("gender", ob) != "女性" )
                addn_temp("xiaxueyi_meet", 1, ob);

        if( present("jinshesword",ob) && !query("no_fight", environment(me))){
                message_vision( CYN"\n$N突然闪身将$n拦下：“留下你的剑来！”\n"NOR,me,ob);
               ob->start_busy(1);
                do_kill(me, ob);
        }

        if( me->is_busy() || me->is_fighting()) return;

        else if( query_temp("xiaxueyi_meet", ob)>2
           && !query("no_fight", environment(me) )
           && query_temp("user_type", ob) != "worker"){
                message_vision( CYN"\n$N冷冷的看了$n一眼，一副不屑的样子。\n"NOR,me,ob);
                ob->start_busy(random(2));
                delete_temp("xiaxueyi_meet", ob);
   //             me->fight_ob(ob); //很早以前就想，xia有这么犯贱么？
   //            ob->fight_ob(me);
        }
}

void throwing()
{
        switch(random(2)) {
                case 0 : command("throw zhui"); break;
                case 1 : command("throw biao"); break;
        }
}

void kill_ob(object me)
{
      command("perform kuangwu");
      ::kill_ob(me);

}

string get_user_place(int i)
{
        object *obs = users(), ob, room;

        i++;
        if( i > 10 ) return 0;

        ob = obs[random(sizeof(obs))];
        room = environment(ob);

        if (wiz_level(ob)
        || ob->is_ghost()
        || !room
         || query("no_fight", room )
        || strsrch(file_name(room),"/d/") < 0
        || !strsrch(base_name(room), "/d/wizard/")
        || !strsrch(base_name(room), "/d/zhiye/")
        || !strsrch(base_name(room), "/d/death/")
        || !strsrch(base_name(room), "/d/wuguan/"))
                return get_user_place(i);

        else return file_name(room);

}
int do_back(object me)
{
        string room;

        remove_call_out("do_back");
        if (!stringp(room = get_user_place(0)))
                me->move("/d/huashan/shanlu1");
        else me->move(room);

        tell_room(environment(me),query("name", me)+"快步走了过来。\n",({me}));
        me->set_leader(0);
        give_weapon();
        me->reincarnate();
        return 1;
}

int checking(object me, object dest)
{
        object ob;
        if (!me || !dest || !present(dest, environment(me))) return 0;
        if (me->is_fighting(dest)){
                call_out("checking", 1, me, dest);
                return 1;
        }

        if( objectp(ob = present("corpse", environment(me)))
           && query("victim_name", ob) == query("name", dest)){
                remove_call_out("checking");
                if( objectp(dest = present("jinshe sword", ob)))
                        destruct(dest);
                command("chat* grin corpse");
                tell_room(environment(me),query("name", me)+"将长衫一摆，快步走了出去。\n"NOR,({me}));
                call_out("do_back", 1, me);
                return 1;
        }

        return 1;
}

int do_kill(object me, object dest)
{
        if( objectp(dest) && present(dest, environment(me))){
                me->set_leader(dest);
                me->kill_ob(dest);
                dest->fight_ob(me);
                checking(me, dest);
        }
        return 1;
}
 int ask_anqi()
{
         object obj, me = this_player();
        if(me->query_skill("jinshe-jianfa",1) <200 )
                  return 1;
        if( query_temp(QUESTDIR+"暗器", me) >= 3){
         command("say 我不是已经给你了吗。");
            return 1; 
            }
       obj= new(BINGQI_D("throwing/jinshe-zhui"));
       obj->move(me);
        message_vision("$N给$n一些"+obj->name()+NOR"。\n",this_object(),me);
          addn_temp(QUESTDIR+"暗器", 1, me);
         command("say 拿好了，这金蛇锥可是我的独门暗器，你要小心使用。");
           return 1; 
 }


int ask_weapon()
{
        object obj, me = this_player();

//        if (!me->query(QUESTDIR+"pass")) {
       if( !query(QUESTDIR+"over", me)){
          command("heng");
            return 1; 
           }

        if( query_temp(QUESTDIR+"金蛇锥", me)){
          command("say 我不是已经给你了吗。");
            return 1; 
            }
       obj= new("/d/huashan/jinshe/obj/jinshe-zhui");
       set("owner",query("id",  me), obj);
       set("no_drop", 1, obj);
       set("no_give", 1, obj);
       obj->move(me);
       message_vision("$N给$n一些"+obj->name()+NOR"。\n",this_object(),me);
          set_temp("quest/金蛇掌法/start", 1, me);//金蛇掌法开始标记凭此可以向温仪询问
          addn_temp(QUESTDIR+"金蛇锥", 1, me);
          command("say 这金蛇锥可是我的独门暗器，以此为信物，你可去温家堡找温仪索要我遗留的宝物。");
            return 1; 
}


int ask_fuchou() 
{
        object me = this_player();

        if(me->query_skill("jinshe-jianfa",1) <200 )
                   return 1;

        if(me->query_condition("killer"))
         {
           command("fear"+query("id", me));
           command("say 小心官府通缉！");
           return 1;
        }

        if( query_temp(QUESTDIR+"start", me) )
  {
          command("shake"+query("id", me));
          command("say 你不是说要帮我复仇的吗，怎么还在这里？");
          return 1;
  } 
        if( query(QUESTDIR+"over", me) )
  {
          command("thank"+query("id", me));
          command("say 你已经杀了温家五老帮我复仇了，真是太感谢了！");
          return 1;
  } 
  //非vip玩家，只能失败三次
  if( query(QUESTDIR+"fail", me) >= 3 && query("registered", me)<3 )
  {
          command("shake"+query("id", me));
          command("say 现在时间紧急，这复仇的事情还是以后再说吧。");
          return 1;
        }
        //需要间隔一天，经验需要间隔500k

        if( query(QUESTDIR+"start/time", me) && time()-query(QUESTDIR+"start/time", me)<86400 )
        {
          command("shake"+query("id", me));
          command("say 今天先这里吧，有什么事情明天再说吧。");
          return 1;
  }
        if( query(QUESTDIR+"start/combat_exp", me) && query("combat_exp", me)-query(QUESTDIR+"start/combat_exp", me)<500000 )
        {
          command("look"+query("id", me));
          command("say 以你当前的经验恐怕还是难以帮我复仇，还是抓紧去练功去吧。");
          return 1;
  }
        
          command("look"+query("id", me));
          command("say 好吧，你去帮我杀掉温家五老，我定有重谢。");
          command("say 你只要和温家五老的老大提起“金蛇郎君”即可。");

          set_temp(QUESTDIR+"start", 1, me);//开始标志
         //标记开始时间和经验
         set(QUESTDIR+"start/time", time(), me);
         set(QUESTDIR+"start/combat_exp",query("combat_exp",  me), me);
          return 1;
}

int ask_jinshe() 
{
        object me = this_player();      
        int exp, neili;
     
       //相关武功等级必须在250以上
        if(me->query_skill("jinshe-jianfa",1) <250 )
                   return 1;
        if(me->query_skill("jinshe-zhangfa",1) <250 )
                   return 1;
          //必须杀死过温家五老
        if( !query(QUESTDIR+"over", me) )
                   return 1;

        if(me->query_condition("killer"))
         {
           command("fear"+query("id", me));
           command("say 小心官府通缉！");
           return 1;
        }

  //非vip玩家，只能失败三次
  if( query(QUESTDIR+"fail", me) >= 3 && query("registered", me)<3 )
  {
          command("shake"+query("id", me));
          command("say 我不是都告诉你了吗，领悟不了可是你自己的事情了。");
          return 1;
        }
        //武功学习之间需要间隔一天，经验需要间隔500k

        if( query(QUESTDIR+"time", me) && time()-query(QUESTDIR+"time", me)<86400 )
        {
          command("shake"+query("id", me));
          command("say 今天先这里吧，有什么事情明天再说吧。");
          return 1;
  }
        if( query(QUESTDIR+"combat_exp", me) && query("combat_exp", me)-query(QUESTDIR+"combat_exp", me)<500000 )
        {
          command("look"+query("id", me));
          command("say 以你当前的经验恐怕还是难以领悟要诀，还是抓紧去练功去吧。");
          return 1;
  }
         exp=700+random(300);
         neili=20+random(30);
          command("look"+query("id", me));
          command("say 既然你帮我报了大仇，我就将我对金蛇秘籍的研究心得告诉你吧。");
         //标记武功的时间和标志
         set(QUESTDIR+"time", time(), me);
         set(QUESTDIR+"combat_exp",query("combat_exp",  me), me);
      if( random(query("kar", me))>22){
           set(QUESTDIR+"pass", 1, me);
         tell_object(me,HIG"\n你听了夏雪宜的指点，再与金蛇秘笈中不解之处一加参照，登时豁然贯通，果然妙用无穷。\n\n"NOR);
        tell_object(me,HIC"\n你闭目冥思，《金蛇秘笈》中种种武功秘奥，有如一道澄澈的小溪，缓缓在心中流过，\n"NOR);
        tell_object(me,HIC"清可见底，更先半分渣滓，直到许久才醒觉。经此一阵苦思，不但通解了金蛇郎君的\n"NOR);
        tell_object(me,HIC"\n武学秘诀，对师父所授诸般上乘武功，也有更深一层体会。\n"NOR);
          command("wa2"+query("id", me));
              tell_object(me,HBYEL"\n你于"+NATURE_D->game_time()+"得到夏雪宜的指点，武学修为精进，获得"+exp+"点经验奖励、"+neili+"点最大内力。\n"NOR);
                addn("combat_exp", exp, me);
                addn("max_neili", neili, me);
                me->set_skill("wudu-yanluobu", 1);
              log_file("quest/jinshequest",sprintf("%s(%s)失败%d次后得到夏雪宜的指点，武学修为精进。奖励：%d点经验，%d点最大内力。\n",me->name(1),query("id", me),query("quest/金蛇剑法/fail", me),exp,neili));

                  return 1;
            }
        tell_object(me,HIR"\n苦思冥想，发现自己依然无法理解夏雪宜所传秘诀。\n\n"NOR);
          command("sigh"+query("id", me));
           addn(QUESTDIR+"fail", 1, me);
       log_file("quest/jinshequest",sprintf("%s(%s)第%d次向夏雪宜求教，但是依然无法理解其中诀窍。\n",me->name(1),query("id", me),query("quest/金蛇剑法/fail", me)));

          return 1;
}
