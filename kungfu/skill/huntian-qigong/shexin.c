// This program is a part of NITAN MudLIB

#include <ansi.h>

#define SLEEP_CMD       "/cmds/std/sleep"

string *msgs = ({
        HIY "$N和悦地对$n说道：“望着我的眼睛，千万不可分神。现在你感到眼皮沉重，头脑发晕，\n"
        "全身疲乏无力，那就闭上眼睛睡罢。”$N越说声音越是柔和甜美。\n"
        "$n微觉不妥，要想转头避开$N的眼光，可是一双眼睛竟似被$N的目光吸住了，不由自主\n"
        "的凝视着$N，竟然不知不觉的哈欠连连。\n" NOR,

        HIW "只见$N笑咪咪的凝望$n，眼中似发光芒。$n一怔，觉得曾在甚么地方和此人会过，\n"
        "又觉得$N眼色瞧得自己极不舒服，当即转头避开，但过不片刻，忍不住又去望了$N一眼\n"
        "$N笑道：“下得好大的雪啊，是不是？”$n道：“是，好大的雪。”$N道：\n"
        "“来，咱们去瞧瞧雪景。”$N说话极是和悦动听，竟有一股中人欲醉之意，$n登时 \n"
        "觉得神倦眼困，全身无力。\n" NOR,

        HIM "突然$n与$N目光相接，不禁心中微微一震，只见$N双目中精光逼射，动人心魄。\n"
        "$N微笑道：“您累啦，您歇歇罢！”声音柔和，极是悦耳动听。$n果觉全身倦怠，\n"
        "心想累了这大半夜，也真该歇歇了，心念这么一动，更是目酸口涩，精疲神困。\n" NOR,
});

string *laughMsg = ({
        HIW "$N越笑越厉害，直笑得满地直打跌，差点闭过气去。\n" NOR,
        HIG "$N捧住肚子，嘻嘻哈哈地直笑得两眼翻白，喘不过气来。\n" NOR,
        HIY "$N继续哈哈大笑，前仰后合，似是听到了最可笑不过的笑话。\n" NOR,
        HIM "但见$n笑得越来越欢畅，不知怎地，$N只觉全身轻飘飘的快美异常，不由自主的\n"
        "哈哈大笑起来。\n" NOR,
        HIC "$N见$n闭目良久，只道已受了自己言语所惑，昏沉睡去，正自欣喜，欲待\n"
        "再施狡计，突见$n睁开双眼，向着自己微微而笑，便也报以微微一笑。\n" NOR,
});

private void delay(object me, object target);
private void fail(object me, object target, int times);
private void wait_kill(object me, object target);
private void start_kill(object target, object me);

void create()
{
        seteuid(getuid());
}

int exert(object me, object target)
{
        object env;

        env = environment(me);

        if( !query("can_exert/huntian-qigong/shexin", me) )
                return notify_fail("咦，你会使用慑心术吗？\n");

        if( query("no_fight", env) || query("no_sleep_room", env )
                 || query("sleep_room", env) || query("hotel", env) )
                return notify_fail("你不可以在这里使用慑心术。\n");

        if (! target)
                return notify_fail("你要对谁使用慑心术？\n");

        if( query("race", target) != "人类" )
                return notify_fail("你能够催眠动物吗？不见得吧？\n");

        if ((int)me->query_skill("huntian-qigong", 1) < 120)
                return notify_fail("你的混天气功修为不够！\n");

        if (target == me)
                return notify_fail("你不能慑自己的心！\n");

        if (! wizardp(me) && wizardp(target))
        {
                message_combatd(RED "大胆！敢对巫师使用慑心术！。\n" NOR, me);
                this_player()->unconcious();
                return 1;
        }

        if( query("no_shexin", target) )
                return notify_fail("无法对此人使用慑心术。\n");

        if (! living(target))
                return notify_fail("你不能慑他的心了！\n");

        if (me->is_fighting() || target->is_fighting())
                return notify_fail("战斗中无法使用慑心术。\n");

        if (target->is_busy()) return notify_fail("此人正忙着呢！\n");

        if( query("max_neili", me)<1000 )
                return notify_fail("你的内力修为不够。\n");

        if( query("neili", me)<500 )
                return notify_fail("你的内力不够。\n");

        message_combatd(CYN "$N发出一阵阴笑。\n" NOR, me);

        me->start_busy(2);
        if( member_array(query("id", me),target->query_killer()) != -1 )
                call_out("delay", 2, me, target);
        else call_out("delay", 1, me, target);

        return 1;
}

private void delay(object me, object target)
{
        string fam;
        int myLev, tarLev, ok;

        if (! me || ! target) return;
        if (! present(target, environment(me)))
        {
                tell_object(me, "很可惜，你的目标已经不在了。\n");
                return;
        }

        if (me->is_fighting() || target->is_fighting())
        {
                tell_object(me,"战斗中无法使用慑心术。\n");
                return;
        }

        message_combatd( msgs[random(3)], me, target);

        myLev=(query("level", me))*(query("neili", me)/100)*(me->query_skill("force")/10);
        tarLev=query("level", target)*(query("neili", target)/100)*(target->query_skill("force")/10);

        if (myLev / 2 > tarLev) ok = 1;
        else if (tarLev / 2 >= myLev) ok = 0;
        else if (myLev / 2 + random(myLev) > tarLev) ok = 1;
        else ok = 0;

        addn("neili", -500, me);
        me->receive_damage("qi", 300);
        set("jiali", 0, me);

        if (ok == 0)
        {
                me->start_busy(15);
                call_out("fail", 1, me, target, 4);
                return;
        }
        /*
        tell_object(target, HIR "\n你只觉得昏昏欲睡，往地下角落一躺，开始睡觉。\n" NOR);
        tell_object(target, HIR "不一会儿，你就进入了梦乡。\n" NOR);
        tell_object(me,"\n"HIY+query("name", target)+"往地下角落屈身一躺，不一会便鼾声大作，做起梦来。\n"NOR);
        */

        me->start_busy(1);
        set_temp("block_msg/all", 1, me);

        fam=query("family/family_name", target);
        if( fam != "丐帮") set("family/family_name", "丐帮", target);

        SLEEP_CMD->main(target);

        if( fam != "丐帮") set("family/family_name", fam, target);

        delete_temp("block_msg/all", me);
        return;

}

private void fail(object me, object target, int times)
{
        if (times != -1)
        {
                message_combatd( "\n" + laughMsg[times], me, target);
                call_out("fail", 2, me, target, times-1);
        }

        else
        {
                message_combatd( HIR "\n$N笑得忽然闭了气。\n" NOR, me);
                me->unconcious();

                if (! userp(target)) call_out("wait_kill", 3, me, target);
                return;
        }
}

private void wait_kill(object me, object target)
{
        if (! target || ! living(target)) return;
        if (environment(me) != environment(target))
        {
                return;
        }

        if (! living(me)) call_out("wait_kill", 2, me,  target);

        else
        {
                message_combatd(HIR "$N对着$n哼了一声：“" +
                                RANK_D->query_self_rude(target)+
                                "明人不做暗事，现在你醒了，拿命来！！”\n"NOR, target, me);
                call_out("start_kill", 0, target, me);
        }
        return;
}

private void start_kill(object target, object me)
{
        me->want_kill(target);
        target->kill_ob(me);
        me->fight_ob(target);
        return;
}
