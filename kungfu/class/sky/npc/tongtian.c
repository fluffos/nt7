// 通天老仙 掌管转世
// Create By Rcwiz 09/2003

#include <ansi.h>

inherit NPC;

#define SCBORN_D   "/adm/daemons/scbornd"
#define MEMBER_D   "/adm/daemons/memberd"

mixed start_scborn();
mixed start_kaoyan();

void create()
{
        set_name(HIW "通天老仙" NOR, ({ "tongtian laoxian", "tongtian", "laoxian" }));
        set("long", HIW "    此乃镇守天外天的天界大神—通天老仙，据说他\n"
                        "掌管着天界转世之路最后一道到大门。\n" NOR);

        set("gender", "男性");
        set("age", 199);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("str", 100);
        set("int", 100);
        set("con", 100);
        set("dex", 100);

        set("max_qi", 200000);
        set("max_jing", 50000);
        set("max_neili", 30000);
        set("neili", 30000);
        set("jiali", 200);
        set("combat_exp", 90000000);

        set_skill("dodge", 550);
        set_skill("parry",550);
        set_skill("unarmed", 550);
        set_skill("yinyang-shiertian", 550);
        set_skill("force", 550);
        set_skill("martial-cognize", 550);
        set_skill("literate", 550);

        map_skill("force", "yinyang-shiertian");
        map_skill("dodge", "yinyang-shiertian");
        map_skill("parry", "yinyang-shiertian");
        map_skill("unarmed", "yinyang-shiertian");
        
        set("inquiry", ([
                "转世"   :   (: start_scborn :),
                "考验"   :   (: start_kaoyan :),
        ]));
        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
        }) );
        setup();

        carry_object(__DIR__"obj/xianpao")->wear();
}

// 转世后考验过12天可以再获得2点轮回点
mixed start_kaoyan()
{
           object me;

           me = this_player();

           if (! me->query("scborn/ok"))
           {
                   write("你还没转世呢。\n");
                   return 0;
           }

       if (me->query("sky12/floor") != 13)
       {
              write("你还没有通过十二重天界的考验！不知道怎么跑来的，快滚！\n");
                          me->move("/d/city/wumiao");
              return 0;
       }

           // 检查是否已经获得过
           if (me->query("scborn/get_lunhui_point_12t"))
           {
                          write("你已经获取过轮回点了。\n");
                          return 0;
           }

           if (me->query("scborn/total_lunhui_point") >= 17)
           {
                          write("数据错误。\n");
                          return 0;
           }

           // 获得轮回点
           me->add("scborn/total_lunhui_point", 2);
           me->add("scborn/cur_lunhui_point", 2);
           me->set("scborn/get_lunhui_point_12t", 1);

           me->save();

           write("恭喜你经过十二重天考验，获得 两 点轮回点。\n");
           return 1;
}


mixed start_scborn()
{
        object me = this_player();
        
        // 检查转世条件
        if (! SCBORN_D->check_data2(me))return 1;

        if (me->query("sky12/haotianta"))
        {
                tell_object(me, HIG "通天老仙对你说道：昊天塔找到了吗？\n" NOR);
                return 1;
        }

        message_sort(HIM "\n$N" HIM "对$n" HIM "说道：人之生老病死、转世轮回皆有定数，"
                     "乃上天注定，如果非要逆天而行，则需打通重重难关，你现在打通了天界"
                     "十二重天，原本应该可以转世重生，但由于你违逆天道，人道，如要顺利"
                     "转世重新做人还需将自身吸入昊天塔中，借用此神器吸星换月之力方可。\n" NOR,
                     this_object(), me);
                     
        tell_object(me, HIG "通天老仙悄悄告诉你：如果你找到昊天塔就把它交给我，我会帮助"
                        "你完成转世！\n" NOR);
        
        me->set("sky12/haotianta", 1);

        return 1;
}

void init()
{
        add_action("do_yhjob", "yhjob");
}

// 选择职业
int do_yhjob(string arg)
{
        object me;
        string msg;

        me = this_player();

    // 介绍
        if (! arg)
        {
                // 一转介绍
                msg  = HIR "\n您目前可以选择以下职业作为您转世后的职业：\n" NOR;
                msg += HIC "侠客：令江湖中人景仰的职业，拥有正气类攻击特技。\n" NOR;
                msg += HIM "魔师: 令世人畏惧的职业，拥有邪异类攻击特技。\n" NOR;
                msg += HIG "隐士: 被世人所遗忘，隐居世外，拥有多种辅助类特技。\n" NOR;
                msg += HIY "具体职业介绍请参见转世职业帮助文件 help scborn_yhjob\n" NOR;
                msg += HIY "请输入指令" HIR " yhjob 职业 " HIY "来选择您转世后的职业，选择前请认真阅读转世职业帮助文件。\n\n" NOR;

                write(msg);
                return 1;        
        }

        if (arg != "侠客" && arg != "魔师" && arg != "隐士")
                return notify_fail("请选择正确的职业：侠客、魔师、隐士。\n");
        
        if (me->query("scborn"))
                return notify_fail("对不起，您不能选择该种职业。\n");

        if (me->query("yhjob/job") && me->query("yhjob/job") != "武士")
                return notify_fail("对不起，您不能选择该种职业。\n");

        write(HIG "您选择了 " + arg + " 的职业。\n");

        me->set("yhjob/job" , arg);
        me->save();

        return 1;
}

int accept_object(object me, object ob)
{        
        string obj;
        string msg;
        string *spes;
        mapping special;
        string job;

                if (me->query("scborn/ok"))
                {
                        write("你已经转过世了。\n");
                        return 0;
                }
                
        // 检查转世条件
        if (! SCBORN_D->check_data2(me))return 0;
        
        obj = filter_color(ob->name());

        if (obj != "昊天塔" || 
            ob->is_item_make() ||
            ! ob->is_magic_item())return 0;

                if (! me->query("yhjob"))
                {
                        write("您还没有选择你转世后的职业呢，请输入指令 yhjob 开始选择您的职业！\n");
                        return 0;
                }

                job = me->query("yhjob/job");

                if (job != "侠客" && job != "魔师" && job != "隐士")
                {
                        write("您选择的职业不正确，请重新选择。\n");
                        return 0;
                }

        // 开始转世
        if (! SCBORN_D->start_scborn(me))
        {
                write("转世时数据出错！\n");
                return 0;
        }
        destruct(ob);

        message_sort(HIC "\n$N" HIC "念起咒语，祭起手中的昊天塔，刹时间，七道光芒从"
                         "昊天塔中奔腾而出，将$n" HIC "卷了进去 ……\n" NOR,
                         this_object(), me);
                         

        me->move("/kungfu/class/sky/haotian");
        tell_object(me, HIG "你穿梭时空，进入了来世！\n\n" NOR);

        me->move("/d/city/wumiao");
                
        special = me->query("special_skill");
        spes = keys(special);
        
        if (MEMBER_D->is_valib_member(me->query("id")) &&
            sizeof(spes) == 2)
        {
                msg = SCBORN_D->get_special_name(spes[0]) + "、";
                msg += SCBORN_D->get_special_name(spes[1]);
        }
        else 
                msg = SCBORN_D->get_special_name(spes[0]);


                // 设置职业技能
                if (job == "侠客")
                {
                        me->set("special_skill/haoran",1);
                        me->set("special_skill/xiagu",1);
                        me->set("special_skill/shewo",1);
                }
                else if (job == "魔师")
                {
                        me->set("special_skill/moxin",1);
                        me->set("special_skill/youran",1);
                        me->set("special_skill/haoling",1);
                }
                else // 隐士
                {
                        me->set("special_skill/haina",1);
                        me->set("special_skill/xianyun",1);
                        me->set("special_skill/tianxia",1);
                }
        // UPDATE_D->born_player(me);

        call_out("notify_all", 1, me, msg, spes);

        return 1;
}

int notify_all(object me, string msg, mixed spes)
{
                CHANNEL_D->do_channel(this_object(), "rumor", 
                               HIY "听说" + me->name() + HIY + 
                               "打通十二重天，穿梭时空，进入了来世！\n" NOR);
         
         tell_object(me, HIW "\n你获得转世技能：" + msg + "\n" NOR);

                 // 获得轮回点
                 tell_object(me, HIG"转世成功，获得 五 点轮回点，以后请使用 power 指令查看。\n");
                 me->add("scborn/total_lunhui_point", 5);
                 me->add("scborn/cur_lunhui_point", 5);

         // 重新设置转世技能，update_d->born_player()要删除所有技能
         if (MEMBER_D->is_valib_member(me->query("id")) &&
             sizeof(spes) == 2)
         {
                me->set("special_skill/" + spes[0], 1);
                me->set("special_skill/" + spes[1], 1);
         }
         else
                me->set("special_skill/" + spes[0], 1);
                
         me->save();
         
         // 通知数据备份消息
         call_out("notify_me", 1, me);
         
         return 1;
}

int notify_me(object me)
{
        tell_object(me, HIR "\n你转世前的数据已备份，七日内如发现数据异常，请及时通知本站admin！\n\n" NOR);
        return 1;
}
void unconcious()
{
        die();
}
