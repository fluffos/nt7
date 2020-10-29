//jianglishi 泥潭奖励使
//smallbear 03.10.26

#include <ansi.h>

inherit NPC;

mixed ask_gongxian();
mixed ask_jiangli();
int do_lingqu(string arg);

void create()
{
        set_name("奖励使", ({ "jiangli shi", "shi", "jiangli" }));
        set("nickname", HIY "泥潭" NOR);
        set("long", "他就是泥潭奖励使，如果你对泥潭有贡献的话，可以到他这里领取奖励。\n");
        set("gender", "男性");
        set("age", 20);
        set("per", 30);
        set("attitude", "peaceful");
        set("inquiry", ([
                "贡献度"   : (: ask_gongxian :),
                "奖励" : (: ask_jiangli :),
        ]));

        setup();
        carry_object("/clone/cloth/jinduan")->wear();
        carry_object("/clone/cloth/xianlv")->wear();
}

void init()
{
        add_action("do_lingqu", "lingqu");
}


mixed ask_gongxian()
{
        object me;
         int gx;

        me = this_player();
         gx=query("hx_gongxian", me);

        if( !query("hx_gongxian", me) )
                return "“你好象还没有为泥潭作出贡献哦，要加油。”";

        if( query("hx_gongxian", me)>0 )
                  write (WHT"奖励使对你笑了笑，说道：“干得好！你现在已经有"+chinese_number(gx)+"点贡献度了，要继续努力哦。”\n"NOR);
        return 1;
}

mixed ask_jiangli()
{
         object me;

         me = this_player();
        
        if( !query("hx_gongxian", me) )
                return "“你还没有贡献度呢，就来问奖励？”";

        if( query("hx_gongxian", me)>0 )
                return "“你是来拿奖励的吗？看一下 help gongxian，然后找我领取吧。”";

         return 1;
}

int do_lingqu(string arg)
{
         object me,ptz,bts,bcs,xd,slw,xsd,hhxd,txyl,jzjd,xhd,mn,fc,zs,sj;
         me = this_player();

        if( !query("hx_gongxian", me) )
                return notify_fail("你目前没有贡献度，不能领取奖励。\n");

         if ( ! arg || arg == "" )
                return notify_fail("你想领取什么呢？\n");

         if ( arg != "菩提子" && arg != "补天石" && arg != "冰蚕丝" && arg != "仙丹" && arg != "神力丸"
&& arg != "洗髓丹" && arg != "火红仙丹" && arg != "天香玉露" && arg != "九转金丹" && arg != "玄黄紫清丹"
&& arg != "玛瑙残片" && arg != "翡翠残片" && arg != "钻石残片" && arg != "水晶残片" )
                return notify_fail("奖励使看了你一眼：“我这里可没有你想要的，决定了再来找我吧。”\n");

         if ( arg == "补天石")
                 {
                         if( query("hx_gongxian", me)<1 )
                                  return notify_fail("你的贡献度不够了，再多多努力吧。\n");
                        
                         write(WHT"奖励使微微点了点头，拿出一块补天石交了给你。\n"NOR); 
                                    addn("hx_gongxian", -1, me);
                                    bts = new("/d/item/obj/butian"); 
                                    bts->move(this_player());
                                    return 1;
                         
                 }

         if ( arg == "冰蚕丝")
                 {
                         if( query("hx_gongxian", me)<1 )
                                  return notify_fail("你的贡献度不够了，再多多努力吧。\n");

                         write(WHT"奖励使微微点了点头，拿出一束冰蚕丝交了给你。\n"NOR); 
                                    addn("hx_gongxian", -1, me);
                                    bcs = new("/d/item/obj/tiancs"); 
                                    bcs->move(this_player());
                                    return 1;
                                   
                 }

         if ( arg == "菩提子")
                 {
                         if( query("hx_gongxian", me)<2 )
                                  return notify_fail("你的贡献度不够了，再多多努力吧。\n");

                         write(WHT"奖励使微微点了点头，拿出一颗菩提子交了给你。\n"NOR); 
                                    addn("hx_gongxian", -2, me);
                                    ptz = new("/d/shaolin/obj/puti-zi"); 
                                    ptz->move(this_player());
                                    return 1;
                                   
                 }

         if ( arg == "仙丹")
                 {
                         if( query("hx_gongxian", me)<4 )
                                  return notify_fail("你的贡献度不够了，再多多努力吧。\n");

                         write(WHT"奖励使微微点了点头，拿出一颗仙丹交了给你。\n"NOR); 
                                    addn("hx_gongxian", -4, me);
                                    xd = new("/clone/gift/xiandan"); 
                                    xd->move(this_player());
                                    return 1;
                                   
                 }

         if ( arg == "神力丸")
                 {
                         if( query("hx_gongxian", me)<4 )
                                  return notify_fail("你的贡献度不够了，再多多努力吧。\n");

                         write(WHT"奖励使微微点了点头，拿出一颗神力丸交了给你。\n"NOR); 
                                    addn("hx_gongxian", -4, me);
                                    slw = new("/clone/gift/shenliwan"); 
                                    slw->move(this_player());
                                    return 1;
                                   
                 }

         if ( arg == "洗髓丹")
                 {
                         if( query("hx_gongxian", me)<4 )
                                  return notify_fail("你的贡献度不够了，再多多努力吧。\n");

                         write(WHT"奖励使微微点了点头，拿出一颗洗髓丹交了给你。\n"NOR); 
                                    addn("hx_gongxian", -4, me);
                                    xsd = new("/clone/gift/xisuidan"); 
                                    xsd->move(this_player());
                                    return 1;
                                   
                 }

         if ( arg == "火红仙丹")
                 {
                         if( query("hx_gongxian", me)<4 )
                                  return notify_fail("你的贡献度不够了，再多多努力吧。\n");

                         write(WHT"奖励使微微点了点头，拿出一颗火红仙丹交了给你。\n"NOR); 
                                    addn("hx_gongxian", -4, me);
                                    hhxd = new("/clone/gift/unknowdan"); 
                                    hhxd->move(this_player());
                                    return 1;
                                   
                 }

         if ( arg == "天香玉露")
                 {
                         if( query("hx_gongxian", me)<4 )
                                  return notify_fail("你的贡献度不够了，再多多努力吧。\n");

                         write(WHT"奖励使微微点了点头，拿出一滴天香玉露交了给你。\n"NOR); 
                                    addn("hx_gongxian", -3, me);
                                    txyl = new("/clone/gift/tianxiang"); 
                                    txyl->move(this_player());
                                    return 1;
                                   
                 }

         if ( arg == "九转金丹")
                 {
                         if( query("hx_gongxian", me)<6 )
                                  return notify_fail("你的贡献度不够了，再多多努力吧。\n");

                         write(WHT"奖励使微微点了点头，拿出一颗九转金丹交了给你。\n"NOR); 
                                    addn("hx_gongxian", -6, me);
                                    jzjd = new("/clone/gift/jiuzhuan"); 
                                    jzjd->move(this_player());
                                    return 1;
                                   
                 }

         if ( arg == "玛瑙残片")
                 {
                         if( query("hx_gongxian", me)<8 )
                                  return notify_fail("你的贡献度不够了，再多多努力吧。\n");

                         write(WHT"奖励使微微点了点头，拿出一片玛瑙残片交了给你。\n"NOR); 
                                    addn("hx_gongxian", -8, me);
                                    mn = new("/clone/gift/cagate"); 
                                    mn->move(this_player());
                                    return 1;
                                   
                 }

         if ( arg == "翡翠残片")
                 {
                         if( query("hx_gongxian", me)<8 )
                                  return notify_fail("你的贡献度不够了，再多多努力吧。\n");

                         write(WHT"奖励使微微点了点头，拿出一片翡翠残片交了给你。\n"NOR); 
                                    addn("hx_gongxian", -8, me);
                                    fc = new("/clone/gift/cjade"); 
                                    fc->move(this_player());
                                    return 1;
                                   
                 }

         if ( arg == "钻石残片")
                 {
                         if( query("hx_gongxian", me)<8 )
                                  return notify_fail("你的贡献度不够了，再多多努力吧。\n");

                         write(WHT"奖励使微微点了点头，拿出一片钻石残片交了给你。\n"NOR); 
                                    addn("hx_gongxian", -8, me);
                                    zs = new("/clone/gift/cdiamond"); 
                                    zs->move(this_player());
                                    return 1;
                }
                 
         if ( arg == "水晶残片")
                {
                         if( query("hx_gongxian", me)<8 )
                                  return notify_fail("你的贡献度不够了，再多多努力吧。\n");
                         write(WHT"奖励使微微点了点头，拿出一片水晶残片交了给你。\n"NOR);
                                    addn("hx_gongxian", -8, me);
                                    sj = new("/clone/gift/ccrystal");
                                    sj->move(this_player());
                                    return 1;
                }
                               
         if ( arg == "玄黄紫清丹")
                {
                         if( query("hx_gongxian", me)<10 )
                                  return notify_fail("你的贡献度不够了，再多多努力吧。\n");

                         write(WHT"奖励使微微点了点头，拿出一颗玄黄紫清丹交了给你。\n"NOR);
                                    addn("hx_gongxian", -10, me);
                                    xhd = new("/clone/gift/xuanhuang");
                                    xhd->move(this_player());
                                    return 1;
                }
                return 1;
}