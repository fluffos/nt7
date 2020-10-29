int do_study(string arg)
{
        string *skill_name = ({
               "strike",          //赵客缦胡缨
               "sword",           //吴钩霜雪明
               "dodge",           //银鞍照白马
               "throwing",        //飒沓如流星
               "pixie-jian",      //十步杀一人 sword
               "qiankundanuoyi",//千里不留行 dodge
               "lingboweibu",     //事了拂衣去 dodge
               "qimen-wuxing",   //深藏身与名 dodge
               "unarmed",         //闲过信陵饮 cuff or strike or unarmed
               "qimen-flee",      //脱剑膝前横 sword
               "parry",           //将炙啖朱亥
               "blade",           //持觞劝侯嬴
               "axe",              //三杯吐然诺 force 暂时先count吧
               "whip",            //五狱倒为轻 cuff or strike or unarmed
               "staff",           //眼花耳热后   鲁达禅杖
               "taoism",          //竞气素霓生 cuff or strike or unarmed
               "hammer",          //救赵挥金锤 sword
               "buddhism",        //邯郸先震惊 force
               "hubo",            //千秋二壮士
               "xiaowuxiang",           //亘赫大梁城 force
               "checking",        //纵死侠骨香   指法
               "club",            //不惭世上英   齐眉棍
               "kuihua-xinfa",    //谁能书阁下
               "taixuan-gong"     //白首太玄经
        });
        object me, where;
        int jing_cost, learn_pot, item, times, i, success=0;
        string skillname;
        int t;

        me = this_player();
        if( !arg ) return notify_fail("你要领悟什么呀？\n");
        if( sscanf(arg, "%s %d", arg, times)!=2)
                return notify_fail("指令格式：think wall <次数>\n");
        if( ( arg != "wall" ) )
                return notify_fail("指令格式：think wall <次数>\n");
        t = 200;
        if( present("study emblem", me) )
                t += 1000;
        if( times < 1 || times > t )
                return notify_fail("领悟次数最少是一次，最多是" + CHINESE_D->chinese_number(t) + "次。\n");
        if( query("combat_exp", me)<500000 )
                return notify_fail("你的经验太低, 没法领悟石壁内容。\n");
        if( (int)me->query_skill("literate", 1) < 1 )
                return notify_fail("你晕了吧! 还是先去学点文化吧。\n");
        jing_cost = 30 + random(me->query_int()/10);
        if( query("jing", me)<jing_cost*times )
                return notify_fail("你现在太累了，领悟不了这么多次，休息一会儿再来吧。\n");
        where = environment(me);
        switch (file_name(where))
        {
                case "/d/xiakedao/shiroom01": item = 0; break;
                case "/d/xiakedao/shiroom02": item = 1; break;
                case "/d/xiakedao/shiroom03": item = 2; break;
                case "/d/xiakedao/shiroom04": item = 3; break;
                case "/d/xiakedao/shiroom05": item = 4; break;
                case "/d/xiakedao/shiroom06": item = 5; break;
                case "/d/xiakedao/shiroom07": item = 6; break;
                case "/d/xiakedao/shiroom08": item = 7; break;
                case "/d/xiakedao/shiroom09": item = 8; break;
                case "/d/xiakedao/shiroom10": item = 9; break;
                case "/d/xiakedao/shiroom11": item = 10; break;
                case "/d/xiakedao/shiroom12": item = 11; break;
                case "/d/xiakedao/shiroom13": item = 12; break;
                case "/d/xiakedao/shiroom14": item = 13; break;
                case "/d/xiakedao/shiroom15": item = 14; break;
                case "/d/xiakedao/shiroom16": item = 15; break;
                case "/d/xiakedao/shiroom17": item = 16; break;
                case "/d/xiakedao/shiroom18": item = 17; break;
                case "/d/xiakedao/shiroom19": item = 18; break;
                case "/d/xiakedao/shiroom20": item = 19; break;
                case "/d/xiakedao/shiroom21": item = 20; break;
                case "/d/xiakedao/shiroom22": item = 21; break;
                case "/d/xiakedao/shiroom23": item = 22; break;
                case "/d/xiakedao/shiroom24": item = 23; break;
                default: break;
        }

        message_vision("$N正在钻研石壁上的图案和注释。\n",me);

        // 不是互搏或太玄则要求最低等级80
        if( me->query_skill(skill_name[item], 1) < 80 ) {
                  if( item != 23 )
                        if( item != 18 ) {
                                write("你望着石壁冥思苦想了一会，发觉上面的东西对你来说太深奥了。\n");
                                return 1;
                        }
        }
        if( me->query_skill(skill_name[item], 1) >= 5900 ) {
                write("你望着石壁冥思苦想了一会，发觉上面的东西对你来说太浅薄了。\n");
                return 1;
        }
        // 辟邪剑法和葵花心法
        if( item == 4 || item == 22 ) {
                if( me->query_skill("pixie-jian", 1) >= 2500 )
                        return notify_fail("你的辟邪剑法已经无法再提高了。\n");
                if( query("gender", me) != "无性"){
                        write("可是壁上是辟邪剑法图谱，欲练神功，必先自宫。\n");
                        return 1;
                }
        } else {
                if( !SKILL_D(skill_name[item])->valid_learn(me) )
                        return SKILL_D(skill_name[item])->valid_learn(me);
        }
        if( (int)(me->query_skill(skill_name[item], 1) *
                me->query_skill(skill_name[item],1)*81) >= query("combat_exp", me)){
                write("你对着石壁冥思苦想了一会，毫无收获。\n");
                return 1;
        }

        learn_pot=random(query("int", me));
        if( learn_pot > 0 ) {
                // 葵花心法
                if( item == 22 ) {
                        me->improve_skill(skill_name[item], times*(random(me->query_kar())+(10+random(me->query_int()-9))/200+1));
                        success = 1;
                }
                else if( item == 4 || item == 5 ) { // 辟邪剑法 | 乾坤大挪移
                        me->improve_skill(skill_name[item], times*(random(me->query_kar())+(10+random(me->query_int()-9))/100+1));
                        success = 1;
                }
                else if( item == 23 || item == 19 ) { // 太玄功 | 小无相
                        //if( me->query_kar() >= 30 )
                        me->improve_skill(skill_name[item], times*(random(me->query_kar())+(10+random(me->query_int()-9))/100+1));
                        success = 1;
                }
                else if( me->query_skill(skill_name[item], 1) > 1000 ) {
                        me->improve_skill(skill_name[item], times*(random(me->query_kar())+(10+random(me->query_int()-9))/30+1));
                        success = 1;
                }
                else {
                        me->improve_skill(skill_name[item], times*(random(me->query_kar())+(10+random(me->query_int()-9))/10+1));
                        success = 1;
                }
//              write("你对着石壁冥思苦想了一会，似乎"+CHINESE_D->chinese(skill_name[item])+"有些心得。\n");
        }
//      else
//              write("你对着石壁冥思苦想了一会，可是成见太深，似乎没啥心得。\n");

        if( success == 1 ) {
                me->receive_damage("jing", times*jing_cost);
                me->receive_damage("qi",times*random(query("int", me)));
                write("你对着石壁冥思苦想了"+chinese_number(times)+"回，似乎对"+CHINESE_D->chinese(skill_name[item])+"有些心得。\n");
        } else {
                me->receive_damage("jing", jing_cost);
                write("你对着石壁冥思苦想了一会，可是成见太深，似乎没啥心得。\n");
        }
        success = 0;
        return 1;
}