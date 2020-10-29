mixed query_book_message(int step)
{
        mixed msg;

        if (step >= sizeof(story))
                return 0;

        msg = story[step];
        if (stringp(msg))
        {
                msg = replace_string(msg, "$N", char_name);
                msg = replace_string(msg, "$ID", char_id);
        }
        return msg;
}

void go_on_process(object ob)
{
        remove_call_out("process_skybook");
        call_out("process_skybook", 1, ob);
}

void process_skybook(object ob)
{
        mixed line;
        object *listeners;
        string prompt;

        go_on_process(ob);

        if (! objectp(ob))
        {
                return;
        }

        line = ob->query_book_message(step);
        step++;

        prompt = ob->prompt();
        if (! prompt) prompt = HIG "【天书】" NOR;
        if (functionp(line)) catch(line = evaluate(line));
        if (stringp(line))
        {
                listeners = filter_array(users(), (: filter_listener :));
                message("skybook",  prompt + WHT + line + "\n" NOR, listeners);
        }

        if (intp(line) && ! line)
        {
                destruct(ob);
        }
}

int filter_listener(object ob)
{
        if( query("env/no_story", ob))return 0;
        return 1;
}

string get_string(string str)
{
        return sprintf("%|60s",str)+"\n";
}

string quest_feihu(object me)
{
        string str= "\n";

        if(!query("quest/雪山飞狐",me))
        {
                str = "------------------------------------------------------------\n";
                str +=get_string(HIW"【目前关于雪山飞狐，没有任何纪录】"NOR);
                return str;
        }

        str =   "------------------------------------------------------------\n";
        str +=get_string(HIW"【雪山飞狐】"NOR);
        str +=  "------------------------------------------------------------\n";
        if(query("quest/雪山飞狐/time",me))
        {
                if(!query("quest/雪山飞狐/解药篇/over",me) )
                        str +=get_string(WHT"游戏纪录时间差："+CHINESE_D->chinese_time(time()-query("quest/雪山飞狐/time",me))+"。"NOR);
                else str +=get_string(WHT"游戏纪录时间："+CHINESE_D->chinese_date(query("quest/雪山飞狐/time",me),1)+"。"NOR);
        }
        if(query("quest/雪山飞狐/combat_exp", me))
        {
                        if(!query("quest/雪山飞狐/解药篇/over",me) )
                                str +=get_string(WHT"游戏纪录经验差："+chinese_number(query("combat_exp",me)-query("quest/雪山飞狐/combat_exp",me))+"。"NOR);
                        else str +=get_string(WHT"游戏纪录经验："+query("quest/雪山飞狐/combat_exp",me)+"。"NOR);
                        str +="\n";
        }
        if(!query("quest/雪山飞狐/两页刀法篇",me))
        {
                str +=get_string(HBRED"游戏纪录混乱。你还需要努力。"NOR);
                str +=feihu_skill(me);
                return str;
        }
        if(!query("quest/雪山飞狐/两页刀法篇/over",me))
        {
                if(random(2)) str +=get_string(HBRED"下一步，如何帮助胡斐进一步完善胡家刀法。"NOR);
                else str +=get_string(HBRED"下一步探索：如何寻找失落的最后两页刀法。"NOR);
                str +=feihu_skill(me);
                return str;
        }

        str +=get_string(YEL"你已经帮助胡斐完善胡家刀法，获得一些奖励。"NOR);

        if(!query("quest/雪山飞狐/复仇篇",me))
        {
                if(random(2)) str +=get_string(HBRED"从阎基处你获得过一些旧事，下一步：辨真假。"NOR);
                else          str +=get_string(HBRED"凶手是苗人凤吗？下一步：闯苗家庄。"NOR);
                str +=feihu_skill(me);
                return str;
        }

        if(!query("quest/雪山飞狐/复仇篇/over",me))
        {
                if(random(2)) str +=get_string(HBRED"当年苗、胡之争，似乎已经明了，只是果真如此吗？"NOR);
                else          str +=get_string(HBRED"看来仇人已经明了，只是真正的凶手真的是苗人风吗？"NOR);
                str +=feihu_skill(me);
                return str;
        }
        str +=get_string(YEL"你已经还原给苗人风和胡斐一个真相，获得一些奖励。"NOR);

        if(!query("quest/雪山飞狐/解药篇",me))
        {
                if(random(2)) str +=get_string(HBRED"但是受小人暗算，苗人风中毒生死未明。"NOR);
                else          str +=get_string(HBRED"20年前的旧事已经明了，复仇之说也算一个完结。"NOR);
                str +=feihu_skill(me);
                return str;
        }

        if(!query("quest/雪山飞狐/解药篇/over",me))
        {
                if(random(2)) str +=get_string(HBRED"真相已经明了，而苗人风中毒生死未明。下一步：寻找解药。"NOR);
                else          str +=get_string(HBRED"20年前的往事已经明了，目前关键是如何寻找治疗苗人风的解药。"NOR);
                str +=feihu_skill(me);
                return str;
        }

        str +=get_string(YEL"五毒教，你成功帮助程灵素夺得七星海棠。"NOR);
        str +=get_string(YEL"药王谷，你成功地炼制解药成功，获得一些奖励。"NOR);

        if(!query("quest/雪山飞狐/宝藏",me))
        {
                str +=get_string(HBRED"你已经完成雪山飞狐的基本情节，最后涉及到一个宝藏。"NOR);
                str +=feihu_skill(me);
                return str;
        }

        str +=   "------------------------------------------------------------\n";
        str +=get_string(HIB"【闯王宝藏】"NOR);
        str +=   "------------------------------------------------------------\n";
        if(query("quest/雪山飞狐/宝藏/time",me))
                str +=get_string(WHT"寻宝纪录时间："+CHINESE_D->chinese_date(query("quest/雪山飞狐/宝藏/time",me),1)+"。"NOR);
        if(query("quest/雪山飞狐/宝藏/combat_exp",me))
        {
                str +=get_string(WHT"寻宝纪录经验："+query("quest/雪山飞狐/宝藏/combat_exp",me)+"。"NOR);
                str +="\n";
        }
        if(!query("quest/雪山飞狐/宝藏/start",me))
        {
                str +=get_string(HBRED"你正在寻找传说中的闯王宝藏。"NOR);
                str +=feihu_skill(me);
                return str;
        }

        str +=get_string(YEL"你已经开始寻找传说中的闯王宝藏。"NOR);
        if(query("quest/雪山飞狐/宝藏/jinku",me))
                str +=get_string(YEL"你已经从闯王宝藏获得大量的财宝，包括黄金等等。"NOR);
        if(query("quest/雪山飞狐/宝藏/yaoku", me))
                str +=get_string(YEL"你发现了闯王药库，并在药库获得增长内力的神奇灵药。"NOR);
        if(query("quest/雪山飞狐/宝藏/bingqiku",me))
                str +=get_string(YEL"你已经挖掘出闯王兵器库的宝物，获得"+chinese_number(query("quest/雪山飞狐/宝藏/bingqiku",me))+"个宝玉。"NOR);
        if(query("quest/雪山飞狐/宝藏/shuku",me))
                str +=get_string(YEL"你从书房发现到一个密室，并在这里寻找到增长经验的神奇灵药。"NOR);
        if(query("quest/雪山飞狐/武功/lengquanshengong",me))
                str +=get_string(YEL"你竟然从一颗灵药里找到一个纸团，并发现冷泉神功秘籍的地点。"NOR);
        else if(query("quest/雪山飞狐/宝藏/shuku",me)>=3)
                str +=get_string(YEL"你从一颗灵药里找到一个似乎是修炼武功的纸团，目前只是未得要领。"NOR);
        str +=feihu_skill(me);
        return str;
}
string feihu_skill(object me)
{
        string str= "";

        if(me->query("quest/雪山飞狐/两页刀法篇/over"))
        {
                str =   "------------------------------------------------------------\n";
                str +=get_string(HIC"【飞狐武功】"NOR);
                str +=  "------------------------------------------------------------\n";
                if(query("quest/雪山飞狐/武功/time",me))
                        str +=get_string(WHT"武功纪录时间："+CHINESE_D->chinese_date(query("quest/雪山飞狐/武功/time",me),1)+"。"NOR);
                if(query("quest/雪山飞狐/武功/combat_exp",me))
                {
                        str +=get_string(WHT"武功纪录经验："+query("quest/雪山飞狐/武功/combat_exp",me)+"。"NOR);
                        str +="\n";
                }
                if(query("quest/雪山飞狐/武功/fight_hu",me))
                {
                   if(query("quest/雪山飞狐/武功/win_hu",me))
                           str +=get_string(HIC"你曾与胡斐进行过"+chinese_number(query("quest/雪山飞狐/武功/fight_hu",me))+"次较量，并获得"+chinese_number(query("quest/雪山飞狐/武功/win_hu",me))+"次胜利。"NOR);
                   else
                           str +=get_string(HIC"你曾与胡斐进行过"+chinese_number(query("quest/雪山飞狐/武功/fight_hu",me))+"次较量，可惜一次也没有胜出。"NOR);
                }

                if(query("quest/雪山飞狐/武功/hujiadaofa",me))
                        str +=get_string(HBYEL"你已经学到了胡家刀法，这门刀法令你的江湖威名大增。"NOR);
                else if(query("quest/雪山飞狐/武功/hujiadaofa_fail",me)>=3 && query("registered",me)<3) // 这个标记有点重复
                        str +=get_string(YEL"你失去了学习胡家刀法的机会，但如果参入VIP，你将获得新的机会。"NOR);
                else if(query("quest/雪山飞狐/武功/hujiadaofa_fail",me) && query("quest/雪山飞狐/武功/hujiadaofa_fail",me)<3 && query("registered",me)<3)
                        str +=get_string(YEL"你失去了学习胡家刀法的"+chinese_number(query("quest/雪山飞狐/武功/hujiadaofa_fail",me))+"次机会，但你还有"+chinese_number(3-query("quest/雪山飞狐/武功/hujiadaofa_fail",me))+"机会。"NOR);
                else if(query("quest/雪山飞狐/武功/hujiadaofa_fail",me))
                        str +=get_string(YEL"你失去了学习胡家刀法的"+chinese_number(query("quest/雪山飞狐/武功/hujiadaofa_fail",me))+"次机会，但你还有无限机会。"NOR);
                else
                        str +=get_string(HBRED"你现在拥有学习胡家刀法的机会。你可以在适当的时候请教胡斐。"NOR);

           if(query("quest/雪山飞狐/解药篇/over",me))
           {
                   if(query("quest/雪山飞狐/武功/fight_miao",me))
                   {
                           if(query("quest/雪山飞狐/武功/win_miao",me))
                                   str +=get_string(HIC"你曾与苗人凤进行过"+chinese_number(query("quest/雪山飞狐/武功/fight_miao",me))+"次较量，并获得"+chinese_number(query("quest/雪山飞狐/武功/win_miao",me))+"次胜利。"NOR);
                           else str +=get_string(HIC"你曾与苗人凤进行过"+chinese_number(query("quest/雪山飞狐/武功/fight_miao",me))+"次较量，可惜一次也没有胜出。"NOR);
                   }
                   if(query("quest/雪山飞狐/武功/miaojiajianfa",me))
                           str +=get_string(HBYEL"你已经学到了苗家剑法，很明显这门剑法对你行走江湖帮助很大。"NOR);
                   else if(query("quest/雪山飞狐/武功/miaojiajianfa_fail",me)>=3 && query("registered",me)<3)
                           str +=get_string(YEL"你浪费了学习苗家剑法的机会，但如果参入VIP，你将获得新的机会。"NOR);
                   else if(query("quest/雪山飞狐/武功/miaojiajianfa_fail",me) && query("quest/雪山飞狐/武功/miaojiajianfa_fail",me)<3 && query("registered",me)<3)
                           str +=get_string(YEL"你失去了学习苗家剑法的"+chinese_number(query("quest/雪山飞狐/武功/miaojiajianfa_fail",me))+"次机会，但你还有"+chinese_number(3-query("quest/雪山飞狐/武功/miaojiajianfa_fail",me))+"机会。"NOR);
                   else if(query("quest/雪山飞狐/武功/miaojiajianfa_fail",me))
                           str +=get_string(YEL"你失去了学习苗家剑法的"+chinese_number(query("quest/雪山飞狐/武功/miaojiajianfa_fail",me))+"次机会，但你还有无限机会。"NOR);
                   else str +=get_string(HBRED"你现在拥有学习苗家剑法的机会。你可以在适当的时候请教苗人风。"NOR);

                   if(query("quest/雪山飞狐/武功/lengquanshengong_teach",me))
                           str +=get_string(HBYEL"你已经发现苗、胡上代的秘密，并从苗人凤处领悟到冷泉神功。"NOR);
                   else if(query("quest/雪山飞狐/武功/lengquanshengong",me))
                           str +=get_string(YEL"你似乎马上要获得冷泉神功的领悟机会。"NOR);
                   else if(query("quest/雪山飞狐/武功/shuku",me)<3 )
                           str +=get_string(YEL"你还有学习冷泉神功的机会。神功据说在宝藏之中。"NOR);
                   else if(query("quest/雪山飞狐/武功/shuku",me)==3 )
                           str +=get_string(YEL"你遇到过一次学习冷泉神功的机会。可惜没有成功。"NOR);
                   else if(query("quest/雪山飞狐/武功/shuku",me)>=4 && query("registered",me)>=3)
                           str +=get_string(YEL"你遇到过两次学习冷泉神功的机会。可惜没有成功。"NOR);
           }
        }
        return str;
}
string quest_lchj(object me)
{
        string str= "\n";

        if(!query("quest/连城诀",me))
        {
                str =    "------------------------------------------------------------\n";
                str +=get_string(HIW"【目前关于连城诀，没有任何纪录】"NOR);
                return str;
        }

        str =   "------------------------------------------------------------\n";
        str +=get_string(HIW"【连城诀】"NOR);
        str +=  "------------------------------------------------------------\n";

        if(query("quest/连城诀/time",me))
        {
                if(!query("quest/连城诀/武馆探密篇/over",me))
                        str +=get_string(WHT"游戏纪录时间差："+CHINESE_D->chinese_time(time()-query("quest/连城诀/time",me))+"。"NOR);
                else str +=get_string(WHT"游戏纪录时间："+CHINESE_D->chinese_date(query("quest/连城诀/time",me),1)+"。"NOR);
        }
        if(query("quest/连城诀/combat_exp",me))
        {
                if(!query("quest/连城诀/武馆探密篇/over",me) && !query("quest/连城诀/武馆探密篇/over",me))
                {
                        if(query("combat_exp",me)> query("quest/连城诀/combat_exp",me))
                                str +=get_string(WHT"游戏纪录经验差："+chinese_number(query("combat_exp",me)-query("quest/连城诀/combat_exp",me))+"。"NOR);
                        else if(query("combat_exp",me)== query("quest/连城诀/combat_exp",me))
                                str +=get_string(WHT"游戏纪录经验差没有任何变化。"NOR);
                        else str +=get_string(WHT"游戏纪录经验超出目前经验："+chinese_number(query("quest/连城诀/combat_exp",me)-query("combat_exp",me))+"。"NOR);
                }
                else str +=get_string(WHT"最后游戏纪录经验："+query("quest/连城诀/combat_exp",me)+"。"NOR);
                str +="\n";
        }

        if(!query("quest/连城诀/雪谷激斗篇",me))
        {
                str +=get_string(HBRED"你正在努力中........"NOR);
                str +=lchj_skill(me);
                return str;
        }
        if(!query("quest/连城诀/雪谷激斗篇/over",me))
        {
                if(random(2)) str +=get_string(HBRED"提示：解密乌蚕衣，寻找雪谷狄云。"NOR);
                else str +=get_string(HBRED"一段冤案，一段往事，一段惊奇，一段悲情。"NOR);
                str +=lchj_skill(me);
                return str;
        }

        str +=get_string(YEL"你从丁典获得乌蚕衣，并在雪谷得遇狄云。"NOR);

        if(!query("quest/连城诀/武馆探密篇/over",me))
        {
                if(random(2)) str +=get_string(HBRED"下一步：密探武馆。也许真相永远将是一个谜。"NOR);
                else          str +=get_string(HBRED"又是传说中的绝世武功和连城财宝，到底真相如何？"NOR);
                str +=lchj_skill(me);
                return str;
        }
        str +=get_string(YEL"你密探武馆，揭开当年冤情，也获得唐诗选辑。"NOR);
        if(query("quest/连城诀/武馆探密篇/baozang",me))
        {
                str +=get_string(YEL"你发现连城宝藏，并从狄云处得知一切。"NOR);
                str +=get_string(YEL"虽然没有身外之财，你从中还是获得部分经验奖励。"NOR);
                str +=lchj_skill(me);
                return str;
        }
        str +=lchj_skill(me);
        return str;
}
string lchj_skill(object me)
{
        string str= "";

        if(query("quest/连城诀/雪谷激斗篇/start",me))
        {
                str =   "------------------------------------------------------------\n";
                str +=get_string(HIB"【连城武功】"NOR);
                str +=  "------------------------------------------------------------\n";
                if(query("quest/连城诀/武功/time",me))
                        str +=get_string(WHT"武功纪录时间："+CHINESE_D->chinese_date(query("quest/连城诀/武功/time",me),1)+"。"NOR);
                if(query("quest/连城诀/武功/combat_exp",me))
                {
                        str +=get_string(WHT"武功纪录经验："+query("quest/连城诀/武功/combat_exp",me)+"。"NOR);
                        str +="\n";
                }
                if(query("quest/连城诀/武功/shenzhao",me)>=2)
                {
                        str +=get_string(HBYEL"你从丁典学到神照经，并更能灵活使用神照绝技。"NOR);
                        str +=get_string(HBYEL"你又从狄云处获得一些经验，对神照经有着更深层次的领悟。"NOR);
                }
                else if(query("quest/连城诀/武功/shenzhao",me)==1)
                {
                        str +=get_string(HBYEL"你从丁典学到神照经，并更能灵活使用神照绝技。"NOR);
                        if(query("quest/连城诀/雪谷激斗篇/over",me))
                        {
                           if(query("quest/连城诀/武功/shenzhao_fail2",me)>=3 && query("registered",me)<3)
                           {
                                   str +=get_string(YEL"但是你失去了从狄云处学习神照经更高层次的领悟机会。"NOR);
                                   str +=get_string(YEL"当然，如果你参入VIP，你将获得新的领悟机会。"NOR);
                           }
                           else if(query("quest/连城诀/武功/shenzhao_fail2",me) && query("quest/连城诀/武功/shenzhao_fail2",me) <3 && query("registered",me)<3)
                                   str +=get_string(YEL"你失去了狄云处领悟神照经的"+chinese_number(query("quest/连城诀/武功/shenzhao_fail2",me))+"次机会，但你还有"+chinese_number(3-query("quest/连城诀/武功/shenzhao_fail2",me))+"机会。"NOR);
                           else if(query("quest/连城诀/武功/shenzhao_fail2",me))
                                   str +=get_string(YEL"你失去了狄云处领悟神照经的"+chinese_number(query("quest/连城诀/武功/shenzhao_fail2",me))+"次机会，但你还有无限机会。"NOR);
                           else str +=get_string(HBRED"你现在拥有从狄云处领悟更高层次神照经的机会。你可以在适当的时候请教狄云。"NOR);
                   }
                }
                else if(query("quest/连城诀/武功/shenzhao_fail",me)>=3 && query("registered",me)<3)
                        str +=get_string(YEL"你失去从丁典领悟神照经的机会，但如果参入VIP，你将获得新的机会。"NOR);
                else if(query("quest/连城诀/武功/shenzhao_fail",me) && query("quest/连城诀/武功/shenzhao_fail",me)<3 && query("registered",me)<3)
                        str +=get_string(YEL"你失去从丁典领悟神照经的"+chinese_number(query("quest/连城诀/武功/shenzhao_fail",me))+"次机会，但你还有"+chinese_number(3-query("quest/连城诀/武功/shenzhao_fail",me))+"机会。"NOR);
                else if(query("quest/连城诀/武功/shenzhao_fail",me))
                        str +=get_string(YEL"你失去从丁典领悟神照经的"+chinese_number(query("quest/连城诀/武功/shenzhao_fail",me))+"次机会，但你还有无限机会。"NOR);
                else str +=get_string(HBRED"你现在拥有领悟神照经的机会。你可以在适当的时候请教丁典。"NOR);

                if(query("quest/连城诀/雪谷激斗篇/over",me))
                {
                        if(query("quest/连城诀/武功/sword",me))
                                str +=get_string(HBYEL"你从狄云学习到躺尸剑法，并更能灵活各种绝技。"NOR);
                        else if(query("quest/连城诀/武功/sword_fail",me)>=3 && query("registered",me)<3)
                        {
                                str +=get_string(YEL"但是你失去学习从狄云处躺尸剑法的机会。\n"NOR);
                                str +=get_string(YEL"当然，如果你参入VIP，你将获得新的领悟机会。"NOR);
                        }
                        else if(query("quest/连城诀/武功/sword_fail",me) && query("quest/连城诀/武功/sword_fail",me) <3 && query("registered",me)<3)
                                str +=get_string(YEL"你失去学习躺尸剑法的"+chinese_number(query("quest/连城诀/武功/sword_fail",me))+"次机会，但你还有"+chinese_number(3-query("quest/连城诀/武功/sword_fail",me))+"机会。"NOR);
                        else if(query("quest/连城诀/武功/sword_fail",me))
                                str +=get_string(YEL"你失去学习躺尸剑法的"+chinese_number(query("quest/连城诀/武功/sword_fail",me))+"次机会，但你还有无限机会。"NOR);
                        else str +=get_string(HBRED"你现在拥有学习躺尸剑法的机会。你可以在适当的时候请教狄云。"NOR);
                }
        }
        return str;
}
string quest_tlbb(object me)
{
        string str= "\n";

        if(!query("quest/天龙八部",me))
        {
                str =    "------------------------------------------------------------\n";
                str +=get_string(HIW"【目前关于天龙八部，没有任何纪录】"NOR);
                return str;
        }

        str =   "------------------------------------------------------------\n";
        str +=get_string(HIW"【天龙八部】"NOR);
        str +=  "------------------------------------------------------------\n";

        if(query("quest/天龙八部/time",me))
        {
                if(!query("quest/天龙八部/复兴天下篇/over",me) && !query("quest/天龙八部/大辽救援篇/over",me))
                        str +=get_string(WHT"游戏纪录时间差："+CHINESE_D->chinese_time(time()-query("quest/天龙八部/time",me))+"。"NOR);
                else str +=get_string(WHT"游戏纪录时间："+CHINESE_D->chinese_date(query("quest/天龙八部/time",me),1)+"。"NOR);
        }
        if(query("quest/天龙八部/combat_exp",me))
        {
                if(!query("quest/天龙八部/复兴天下篇/over",me) && !query("quest/天龙八部/大辽救援篇/over",me))
                {
                        if(query("combat_exp",me)> query("quest/天龙八部/combat_exp",me))
                                str +=get_string(WHT"游戏纪录经验差："+chinese_number(query("combat_exp",me)-query("quest/天龙八部/combat_exp",me))+"。"NOR);
                        else if(query("combat_exp",me)== query("quest/天龙八部/combat_exp",me))
                                str +=get_string(WHT"游戏纪录经验差没有任何变化。"NOR);
                        else str +=get_string(WHT"游戏纪录经验超出目前经验："+chinese_number(query("quest/天龙八部/combat_exp",me)-query("combat_exp",me))+"。"NOR);
                }
                else str +=get_string(WHT"最后游戏纪录经验："+query("quest/天龙八部/combat_exp",me)+"。"NOR);
                str +="\n";
        }

        if(!query("quest/天龙八部/凌波微步篇",me))
        {
                str +=get_string(HBRED"你正在努力中........"NOR);
                str +=tlbb_skill(me);
                return str;
        }
        if(!query("quest/天龙八部/凌波微步篇/over",me))
        {
                if(!query("quest/天龙八部/凌波微步篇/wuliangover",me))
                {
                        if(random(2)) str +=get_string(HBRED"如何寻找段誉，据说在无量山。正在探索中。"NOR);
                        else str +=get_string(HBRED"寻找失踪的段誉中，注意别忘记随便解密凌波微步和北溟神功。"NOR);
                }
                else
                {
                        if(random(2)) str +=get_string(HBRED"从无量山回来的段誉却被劫持到万劫谷。正在探索中。"NOR);
                        else str +=get_string(HBRED"寻找失踪的段誉中，注意小心有高手阻截。"NOR);
                }
                return str;
        }

        str +=get_string(YEL"你已经将段誉从万劫谷救回，并获得一些奖励。"NOR);

        if(!query("quest/天龙八部/天龙营救篇/over",me))
        {
                if(random(2)) str +=get_string(HBRED"下一步：天龙寺大战。倒霉的段誉又牵涉其中，当然只有你来帮忙。"NOR);
                else          str +=get_string(HBRED"西夏第一佛法高僧，武功也是深不可测，能阻止他的只有你了。"NOR);
                str +=tlbb_skill(me);
                return str;
        }

        str +=get_string(YEL"你阻大轮高手于殿外，救段誉于西夏，并获得一些奖励。"NOR);

        if(!query("quest/天龙八部/萧峰身世篇/over",me))
        {
                if(random(2)) str +=get_string(HBRED"谁是小人，谁是英雄，中原旧事，究竟多少秘密被湮灭。"NOR);
                else          str +=get_string(HBRED"竹林惊变，聚闲庄大战，颂摩崖遗魂，历史还我真相..."NOR);
                str +=tlbb_skill(me);
                return str;
        }
        str +=get_string(YEL"聚闲庄，你解救了萧峰成功脱离现场；"NOR);
        str +=get_string(YEL"颂摩崖，你成功揭开崖壁遗书的秘密。"NOR);
        if(query("quest/天龙八部/萧峰身世篇/good",me))
                str +=get_string(YEL"你更是成功说服了萧峰归隐江湖，获得部分奖励。"NOR);
        if(query("quest/天龙八部/萧峰身世篇/bad",me))
                str +=get_string(YEL"你更是成功了击退了契丹人萧峰，获得部分奖励。"NOR);

        if(query("quest/天龙八部/复兴天下篇/start",me))
        {
                if(!query("quest/天龙八部/复兴天下篇/over",me))
                        str +=get_string(HBRED"为独霸武林，联手慕容，江湖上，毕竟还是得看拳头的。"NOR);
                else
                        str +=get_string(YEL"你独闯少林大败群丐，击退无名神僧与萧峰联手，为天下第一。"NOR);
                str +=tlbb_skill(me);
                return str;
        }
        if(query("quest/天龙八部/大辽救援篇/start",me))
        {
                if(!query("quest/天龙八部/大辽救援篇/over",me))
                        str +=get_string(HBRED"萧峰为百姓找想，誓不战争，此人当要救的。只是危险重重。"NOR);
                else
                        str +=get_string(YEL"你完胜中原群雄，并潜入大辽，成功营救萧峰，为侠义豪杰。"NOR);
                str +=tlbb_skill(me);
                return str;
        }
        str +=tlbb_skill(me);
        return str;
}
string tlbb_skill(object me)
{
        string str= "";

        if(query("quest/天龙八部/武功", me))
        {
                str =   "------------------------------------------------------------\n";
                str +=get_string(HIC"【天龙武功】"NOR);
                str +=  "------------------------------------------------------------\n";
                if(query("quest/天龙八部/武功/time",me))
                        str +=get_string(WHT"最后学习纪录时间："+CHINESE_D->chinese_date(query("quest/天龙八部/武功/time",me),1)+"。"NOR);
                if(query("quest/天龙八部/武功/combat_exp",me))
                {
                        str +=get_string(WHT"最后学习纪录经验："+query("quest/天龙八部/武功/combat_exp",me)+"。"NOR);
                        str +="\n";
                }
                if(query("quest/天龙八部/武功/yuxiang",me))
                {
                        if(query("quest/天龙八部/凌波微步篇/over",me))
                                str +=get_string(YEL"你找到MM的玉像，并获得一些提示。你获得记载凌波微步的帛卷。"NOR);
                        else
                                str +=get_string(YEL"你找到MM的玉像，并获得一些提示。"NOR);
                }
                if(query("quest/天龙八部/北冥神功/pass",me))
                        str +=get_string(HBYEL"在无量山洞中你已经学到了北冥神功绝学。"NOR);
                else if(query("quest/天龙八部/北冥神功/fail",me)>=3 && query("registered",me)<3)
                {
                        str +=get_string(YEL"但是你浪费了学习北冥神功的机会。"NOR);
                        str +=get_string(YEL"当然，如果你参入VIP，你将获得新的领悟机会。"NOR);
                }
                else if(query("quest/天龙八部/北冥神功/fail",me))
                {
                        str +=get_string(YEL"但是你失去了学习北冥神功的"+chinese_number(query("quest/天龙八部/北冥神功/fail",me))+"次机会。"NOR);
                        str +=get_string(YEL"但你还有机会学习，新的帛卷可以从玉像处重新获得。"NOR);
                }
                else str +=get_string(HBRED"你现在拥有学习北冥神功的机会。"NOR);

                if(query("quest/天龙八部/武功/pass",me))
                        str +=get_string(HBYEL"并从中已经学到了凌波微步。"NOR);
                else if(query("quest/天龙八部/武功/fail",me)>=3 && query("registered",me)<3)
                {
                        str +=get_string(YEL"但是你浪费了学习凌波微步的机会。"NOR);
                        str +=get_string(YEL"当然，如果你参入VIP，你将获得新的领悟机会。"NOR);
                }
                else if(query("quest/天龙八部/武功/fail",me))
                {
                        str +=get_string(YEL"但是你失去了学习凌波微步的"+chinese_number(query("quest/天龙八部/武功/fail",me))+"次机会。"NOR);
                        str +=get_string(YEL"但你还有机会学习，新的帛卷可以从玉像处重新获得。"NOR);
                }
                else str +=get_string(HBRED"你现在拥有学习凌波微步的机会。"NOR);
        }
        if(query("quest/tonglao/quest",me))
        {
                if(query("quest/tonglao/pass",me))
                        str +=get_string(YEL"你曾"+chinese_number(query("quest/tonglao/quest",me))+"次见到天山灯火，偶救天山童姥，并学到绝世武功。"NOR);
                else if(query("quest/tonglao/second",me))
                        str +=get_string(YEL"你曾"+chinese_number(query("quest/tonglao/quest",me))+"次见到天山灯火，偶救天山童姥。"NOR);
                else str +=get_string(YEL"你曾"+chinese_number(query("quest/tonglao/quest",me))+"次见到天山灯火，但什么也没发现。"NOR);
        }

        if(query("quest/天龙八部/武功/quanli",me))
                str +=get_string(HBYEL"你从萧峰那里领悟到“返璞归真”的武功真谛。"NOR);
        return str;
}

string quest_shediao(object me)
{
        string str= "\n";

        if(!me->query("quest/射雕英雄传"))
        {
                str =    "------------------------------------------------------------\n";
                str +=get_string(HIW"【目前关于射雕英雄传，没有任何纪录】"NOR);
                return str;
        }

        str =   "------------------------------------------------------------\n";
        str +=get_string(HIW"【射雕英雄传】"NOR);
        str +=  "------------------------------------------------------------\n";

        if(query("quest/射雕英雄传/time",me))
        {
                if(!query("quest/射雕英雄传/风雪惊变/over",me) )
                        str +=get_string(WHT"游戏纪录时间差："+CHINESE_D->chinese_time(time()-query("quest/射雕英雄传/time",me))+"。"NOR);
                else str +=get_string(WHT"游戏纪录时间："+CHINESE_D->chinese_date(query("quest/射雕英雄传/time",me),1)+"。"NOR);
        }
        if(query("quest/射雕英雄传/combat_exp",me))
        {
                if(!query("quest/射雕英雄传/风雪惊变/over",me) )
                {
                        if(query("combat_exp",me)> query("quest/射雕英雄传/combat_exp",me))
                                str +=get_string(WHT"游戏纪录经验差："+chinese_number(query("combat_exp",me)-query("quest/射雕英雄传/combat_exp",me))+"。"NOR);
                        else if(query("combat_exp",me)== query("quest/射雕英雄传/combat_exp",me))
                                str +=get_string(WHT"游戏纪录经验差没有任何变化。"NOR);
                        else str +=get_string(WHT"游戏纪录经验超出目前经验："+chinese_number(query("quest/射雕英雄传/combat_exp",me)-query("combat_exp",me))+"。"NOR);
                                str +=get_string(HIC"你已经成功救下杨铁心、郭啸天两位大侠，并获得一些奖励。"NOR);
                }
                else str +=get_string(WHT"最后游戏纪录经验："+query("quest/射雕英雄传/combat_exp",me)+"。"NOR);
                str +="\n";
        }
        else
        {

        }

        str +=shediao_skill(me);
        return str;
}

string shediao_skill(object me)
{
        string str= "";

        if(query("quest/射雕英雄传/yangjiaqiang",me))
        {
                str =   "------------------------------------------------------------\n";
                str +=get_string(HIC"【射雕武功】"NOR);
                str +=  "------------------------------------------------------------\n";
                if(query("quest/射雕英雄传/yangjiaqiang/time",me))
                        str +=get_string(WHT"最后学习纪录时间："+CHINESE_D->chinese_date(query("quest/射雕英雄传/yangjiaqiang/time",me),1)+"。"NOR);
                if(query("quest/射雕英雄传/yangjiaqiang/combat_exp",me))
                {
                        str +=get_string(WHT"最后学习纪录经验："+query("quest/射雕英雄传/yangjiaqiang/combat_exp",me)+"。"NOR);
                        str +="\n";
                }
                if(query("quest/射雕英雄传/风雪惊变/over",me))
                {
                                str +=get_string(YEL"你成功救援郭啸天、杨铁心两家，并获得一些奖励。"NOR);
                }
                if(query("quest/射雕英雄传/yangjiaqiang/pass",me))
                        str +=get_string(HBYEL"并从中已经学到了杨家枪。"NOR);
                else if(query("quest/射雕英雄传/yangjiaqiang/fail",me)>=3 && query("registered",me)<3)
                {
                        str +=get_string(YEL"但是你浪费了学习杨家枪的机会。"NOR);
                        str +=get_string(YEL"当然，如果你参入VIP，你将获得新的学习机会。"NOR);
                }
                else if(query("quest/射雕英雄传/yangjiaqiang/fail",me))
                {
                        str +=get_string(YEL"但是你失去了学习杨家枪的"+chinese_number(query("quest/射雕英雄传/yangjiaqiang/fail",me))+"次机会。"NOR);
                        str +=get_string(YEL"但你还有机会学习，在适当的时候可以去寻找杨铁心请教。"NOR);
                }
                else str +=get_string(HBRED"你现在拥有学习杨家枪的机会。"NOR);
        }
        if(query("quest/jiuyin1/pass",me))
                str +=get_string(HBYEL"你从周伯通处获得了闻名天下九阴真经上卷。"NOR);
        if(query("quest/jiuyin2/pass",me))
                str +=get_string(HBYEL"你从陈玄风处获得了臭名昭著九阴真经下卷。"NOR);
        return str;
}
