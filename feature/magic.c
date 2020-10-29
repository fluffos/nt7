//魔法系统 by wenwu on 2005.9.23

#include <ansi.h>

//魔法防御(防御方me,攻击方ob,造成伤害damage)
int magic_parry(object me,object ob,int damage)
{
        int damage_magic;
if (damage > 0)
{
        switch(me->query("wuxing/mofa"))
        {
                case 0:
                        if (ob->query("wuxing/mofa") == 8)
                        {
                                if (random(9) > 4)
                                {
                                        damage_magic = damage*3/5;
                                        message_vision(NOR"\n$N的光明力量和$n的黑暗力量以一种极不稳定的形态相互冲撞激荡.....\n"HIW"突然$N身上强光一闪，$N的光明力量似乎摆脱了$n的黑暗力量的束缚在$N身前形成一道光之屏障。\n"NOR,me,ob );
                                        tell_object(me, HIM"你的光明力量额外防御了"+damage*2/5+"点伤害。\n"NOR);
                                }
                                else
                                {
                                        damage_magic = damage*7/5;
                                        message_vision(NOR"\n$N的光明力量和$n的黑暗力量以一种极不稳定的形态相互冲撞激荡.....\n突然$n身上的黑暗气息变得更加深沉，一丝黑气聚成一条细线直射向$N的前胸。\n"NOR,me,ob );
                                        tell_object(ob, HIM"你的黑暗力量造成"+damage*2/5+"点的额外伤害。\n"NOR);
                                }
                        }
                        else
                        {
                                if (random(9) > 4)
                                {
                                        damage_magic = damage*4/5;
                                        message_vision(HIW"\n$N身上突然流光异彩，一道淡淡的光之屏障挡在$N身前。\n"NOR,me);
                                        tell_object(me, HIM"你的光明力量额外防御了"+damage*1/5+"点伤害。\n"NOR);
                                }
                                else
                                {
                                        damage_magic = damage;
                                }
                        }
                        break;

                case 1:
                        if (random(9) > 4)
                        {
                                if (ob->query("wuxing/mofa") == 2)
                                {
                                        damage_magic = damage*3/5;
                                        message_vision(HIY"\n$N身上突然黄光一闪，地之护盾出现在在$N身前。\n"NOR,me);
                                        tell_object(me, HIM"你的地之力量额外防御了"+damage*2/5+"点伤害。\n"NOR);
                                }
                                else if (ob->query("wuxing/mofa") == 4)
                                {
                                        damage_magic = damage*7/5;
                                        message_vision(HIG"\n$n身上青光一闪，$N脚下地面突然裂开，一木桩直直撞向$N下盘。\n"NOR,me,ob);
                                        tell_object(ob, HIM"你的木之力量造成"+damage*2/5+"点的额外伤害。\n"NOR);
                                }
                                else
                                {
                                        damage_magic = damage*4/5;
                                        message_vision(HIY"\n$N身上突然黄光一闪，地之盾出现在在$N身前。\n"NOR,me);
                                        tell_object(me, HIM"你的地之力量额外防御了"+damage*1/5+"点伤害。\n"NOR);
                                }
                        }
                        else
                                damage_magic = damage;
                        break;

                case 2:
                        if (random(9) > 4)
                        {
                                if (ob->query("wuxing/mofa") == 4)
                                {
                                        damage_magic = damage*3/5;
                                        message_vision(HIR"\n$N身上突然红光一闪，$N身前凭空出现一道火墙。\n"NOR,me);
                                        tell_object(me, HIM"你的火之力量额外防御了"+damage*2/5+"点伤害。\n"NOR);
                                }
                                else if (ob->query("wuxing/mofa") == 3)
                                {
                                        damage_magic = damage*7/5;
                                        message_vision(HIW"\n$n身上白光一闪，凭空出现一排水箭径直向$N射去。\n"NOR,me,ob);
                                        tell_object(ob, HIM"你的水之力量造成"+damage*2/5+"点的额外伤害。\n"NOR);
                                }
                                else
                                {
                                        damage_magic = damage*4/5;
                                        message_vision(HIR"\n$N身上突然红光一闪，一道火之屏障出现在$N身前。\n"NOR,me);
                                        tell_object(me, HIM"你的火之力量额外防御了"+damage*1/5+"点伤害。\n"NOR);
                                }
                        }
                        else
                                damage_magic = damage;
                        break;

                case 3:
                        if (random(9) > 4)
                        {
                                if (ob->query("wuxing/mofa") == 10)
                                {
                                        damage_magic = damage*3/5;
                                        message_vision(HIW"\n$N身上突然白光一闪，$N身前凭空出现一道水墙。\n"NOR,me);
                                        tell_object(me, HIM"你的水之力量额外防御了"+damage*2/5+"点伤害。\n"NOR);
                                }
                                else if (ob->query("wuxing/mofa") == 1)
                                {
                                        damage_magic = damage*7/5;
                                        message_vision(HIY"\n$n身上黄光一闪，$N脚下地面突然突起成锥状顶向$n。\n"NOR,me,ob);
                                        tell_object(ob, HIM"你的土之力量造成"+damage*2/5+"点的额外伤害。\n"NOR);
                                }
                                else
                                {
                                        damage_magic = damage*4/5;
                                        message_vision(HIW"\n$N身上突然白光一闪，一道水之屏障出现在$N身前。\n"NOR,me);
                                        tell_object(me, HIM"你的水之力量额外防御了"+damage*1/5+"点伤害。\n"NOR);
                                }
                        }
                        else
                                damage_magic = damage;
                        break;

                case 4:
                        if (random(9) > 4)
                        {
                                if (ob->query("wuxing/mofa") == 1)
                                {
                                        damage_magic = damage*3/5;
                                        message_vision(HIG"\n$N身上突然青光一闪，一排参天巨树挡在了$N的身前。\n"NOR,me);
                                        tell_object(me, HIM"你的木之力量额外防御了"+damage*2/5+"点伤害。\n"NOR);
                                }
                                else if (ob->query("wuxing/mofa") == 10)
                                {
                                        damage_magic = damage*7/5;
                                        message_vision(HIY"\n$n身上金芒一闪，一排金剑凭空出现径直射向$N。\n"NOR,me,ob);
                                        tell_object(ob, HIM"你的金之力量造成"+damage*2/5+"点的额外伤害。\n"NOR);
                                }
                                else
                                {
                                        damage_magic = damage*4/5;
                                        message_vision(HIG"\n$N身上突然青光一闪，一排巨木出现在$N身前。\n"NOR,me);
                                        tell_object(me, HIM"你的木之力量额外防御了"+damage*1/5+"点伤害。\n"NOR);
                                }
                        }
                        else
                                damage_magic = damage;
                        break;

                case 5:
                        if (random(9) > 4)
                        {
                                damage_magic = damage*4/5;
                                message_vision(NOR"\n$N的身影突然变得朦胧，一道旋风凭空卷起护在$N周围。\n"NOR,me);
                                tell_object(me, HIM"你的气之力量额外防御了"+damage*1/5+"点伤害。\n"NOR);
                        }
                        else
                                damage_magic = damage;
                        break;

                case 6:
                        if (random(9) > 4)
                        {
                                damage_magic = damage*4/5;
                                message_vision(HIB"\n$N身上电光闪烁，强大的电流在$N周围形成一圈薄薄的磁场结界。\n"NOR,me);
                                tell_object(me, HIM"你的雷之力量额外防御了"+damage*1/5+"点伤害。\n"NOR);
                        }
                        else
                                damage_magic = damage;
                        break;

                case 7:
                        if (random(9) > 4)
                        {
                                damage_magic = damage*4/5;
                                message_vision(HIM"\n$N周身罩上一层淡淡的紫色光晕，一面精神之护盾突然出现在$N身前。\n"NOR,me);
                                tell_object(me, HIM"你的心灵力量额外防御了"+damage*1/5+"点伤害。\n"NOR);
                        }
                        else
                                damage_magic = damage;
                        break;

                case 8:
                        if (ob->query("wuxing/mofa") == 0)
                        {
                                if (random(9) > 4)
                                {
                                        damage_magic = damage*3/5;
                                        message_vision(NOR"\n$N的黑暗力量和$n的光明力量以一种极不稳定的形态相互冲撞激荡.....\n突然$N身上黑暗气息大盛，$N的黑暗力量冲破了$n光明力量的约束在$N周围形成一道黑暗天幕。\n"NOR,me,ob );
                                        tell_object(me, HIM"你的黑暗力量额外防御了"+damage*2/5+"点伤害。\n"NOR);
                                }
                                else
                                {
                                        damage_magic = damage*7/5;
                                        message_vision(NOR"\n$N的黑暗力量和$n的光明力量以一种极不稳定的形态相互冲撞激荡.....\n突然$n身上强光大盛，一柄光之剑只指$N前胸。\n"NOR,me,ob );
                                        tell_object(ob, HIM"你的光明力量造成"+damage*2/5+"点的额外伤害。\n"NOR);
                                }
                        }
                        else
                        {
                                if (random(9) > 4)
                                {
                                        damage_magic = damage*4/5;
                                        message_vision(NOR"\n$N的身影突然变得模糊难见，一层漆黑的雾气笼罩在$N在身周。\n"NOR,me);
                                        tell_object(me, HIM"你的黑暗力量额外防御了"+damage*1/5+"点伤害。\n"NOR);
                                }
                                else
                                {
                                        damage_magic = damage;
                                }
                        }
                        break;

                case 9:
                        if (random(9) > 4)
                        {
                                damage_magic = damage*4/5;
                                message_vision(HIC"\n$N的身形突然凭空消失，$N原来所在的位置既然形成一虚无的空间断层。\n"NOR,me);
                                tell_object(me, HIM"你的空间力量额外防御了"+damage*1/5+"点伤害。\n"NOR);
                        }
                        else
                                damage_magic = damage;
                        break;

                case 10:
                        if (random(9) > 4)
                        {
                                if (ob->query("wuxing/mofa") == 1)
                                {
                                        damage_magic = damage*3/5;
                                        message_vision(HIY"\n$N身上突然金芒一闪，$N周身皮肤犹如金铁质化泛出淡淡金光。\n"NOR,me);
                                        tell_object(me, HIM"你的金之力量额外防御了"+damage*2/5+"点伤害。\n"NOR);
                                }
                                else if (ob->query("wuxing/mofa") == 2)
                                {
                                        damage_magic = damage*7/5;
                                        message_vision(HIR"\n$n身上红光一闪，一道火焰凭空出现径直卷向$N。\n"NOR,me,ob);
                                        tell_object(ob, HIM"你的火之力量造成"+damage*2/5+"点的额外伤害。\n"NOR);
                                }
                                else
                                {
                                        damage_magic = damage*4/5;
                                        message_vision(HIY"\n$N身上突然金光一闪，$N周身皮肤犹如银铁质化泛出淡淡银光。\n"NOR,me);
                                        tell_object(me, HIM"你的金之力量额外防御了"+damage*1/5+"点伤害。\n"NOR);
                                }
                        }
                        else
                                damage_magic = damage;
                        break;

                        default:damage_magic = damage;
        }
        return damage_magic;
}
else
        return damage;
}