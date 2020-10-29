void init()
{
        add_action("do_look","look");
        add_action("do_type","type");
}

int do_look(string arg)
{
        int i;
        string msg;
        mapping *bunch_quest,*bunch_zs;

        if (!arg || arg != "paizi")
                return 0;

        if( time()-query_temp("last_look_paizi", this_player())<2 )
        {
                tell_object(this_player(),"别挤，大家都要看！你刚看过了，等一下再看吧！\n");
                return 1;
        }

        bunch_zs = PARTY_QUEST_D->query_zhuisha_quest(TYPE);
        bunch_quest = PARTY_QUEST_D->query_city_quest(PLACE, TYPE);
        bunch_zs = sort_array(bunch_zs,(: sort_by_id :));
        bunch_quest = sort_array(bunch_quest,(: sort_by_id :));

        msg = HIC "----------------------------------------------------------------------------\n"NOR;
        msg += WHT BBLU "                                  追杀令                                    \n"NOR;
        msg += HIC "----------------------------------------------------------------------------\n"NOR;
        msg += sprintf(HIR"%-10s%-50s%-10s%s\n"NOR,"编号","任务","难度","奖励");
        if (sizeof(bunch_zs))
                for (i=0;i<sizeof(bunch_zs);i++)
                        msg += sprintf("%-10s%-50s%-10s%s\n",
                                          bunch_zs[i]["id"],
                                          "追杀"+bunch_zs[i]["name"],
                                          bunch_zs[i]["difficult"],
                                          bunch_zs[i]["reward"],
                                      );
        msg += HIC "----------------------------------------------------------------------------\n"NOR;
        msg += WHT BBLU "                                  任务表                                    \n"NOR;
        msg += HIC "----------------------------------------------------------------------------\n"NOR;
        msg += sprintf(HIR"%-10s%-50s%-10s%s\n"NOR,"编号","任务","难度","奖励");
        if (sizeof(bunch_quest))
                for (i=0;i<sizeof(bunch_quest);i++)
                {
                        if (bunch_quest[i]["id"] == "xc" && !bunch_quest[i]["enable"]) continue;
                        msg += sprintf("%-10s%" + sprintf("%d", (50 + color_len(bunch_quest[i]["name"]))) + "-s%-10s%s\n",
                                          bunch_quest[i]["id"],
                                          bunch_quest[i]["name"],
                                          bunch_quest[i]["difficult"],
                                          bunch_quest[i]["reward"],
                                      );
                }
        msg += HIC "----------------------------------------------------------------------------\n"NOR;
        msg += HIC "请用type <编号>查看每个任务的具体情况。\n"NOR;
        msg += HIC "请用choose <编号>选择你要完成的任务，放弃任务用giveup指令。\n"NOR;

        set_temp("last_look_paizi", time(), this_player());
        this_player()->start_more(msg);
        return 1;
}

int do_type(string arg)
{
        string msg;
        mapping bunch_quest;

        if (!wizardp(this_player()) &&  
            (bad_bunch(this_player()) || query("shen", this_player())<0) )
                return notify_fail("你一个黑道人士到这里来查什么任务？\n");

        if (!wizardp(this_player()) && ! good_bunch(this_player()))
                return notify_fail("你先加入白道联盟，才可以查看白道的任务。\n");

        if (!arg) 
                return notify_fail("你想查看哪条任务的详细信息？指令：type <编号>\n");

        bunch_quest = PARTY_QUEST_D->query_zhuisha_quest(TYPE, arg);

        if (!bunch_quest)     
                bunch_quest = PARTY_QUEST_D->query_city_quest(PLACE,TYPE, arg);

        if (!bunch_quest)
                return notify_fail("你所查询的编号为"+arg+"的任务并不存在。\n");
        
/*      if (bunch_quest["id"] == "xc" && !bunch_quest["enable"]) 
                return notify_fail("今天已经有弟兄去巡城了，你等改天吧。\n");
*/
        msg = HIC "\n----------------------------------------------------------------------------\n"NOR;
        msg += "任务编号：" + bunch_quest["id"] + "\n";
        msg += "任务类型：" + bunch_quest["type"] + "\n";
        msg += "任务名称：" + bunch_quest["name"] + "\n";
        msg += "任务难度：" + bunch_quest["difficult"] + "\n";
        msg += "任务奖励：" + bunch_quest["reward"] + "\n";
        msg += "任务信息: \n" + bunch_quest["msg"] + "\n";
        msg += HIC "----------------------------------------------------------------------------\n"NOR;
        this_player()->start_more(msg);
        return 1;
}

int sort_by_id(mapping quest1, mapping quest2)
{
          return strcmp(quest1["id"], quest2["id"]);
}
