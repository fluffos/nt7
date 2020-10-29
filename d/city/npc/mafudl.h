int do_ridedl()
{
        string hname;
        object ob = this_player();
        int i;
        string *yz_dl = ({
                HIC"客店"NOR,
                HIC"北大街"NOR,
                HIC"中央广场"NOR,
                HIC"南大街"NOR,
                HIC"南大街"NOR,
                HIC"南门"NOR,
                HIC"青石大道"NOR,
                HIC"青石大道"NOR,
                HIC"青石大道"NOR,
                HIC"青石大道"NOR,
                HIC"青石大道"NOR,
                HIC"小路"NOR,
                HIC"小路"NOR,
                HIC"小路"NOR,
                HIC"三不管"NOR,
                HIC"大道"NOR,
                HIC"小路"NOR,
                HIC"小路"NOR,
                HIC"青石阶"NOR,
                HIC"青石阶"NOR,
                HIC"青石阶"NOR,
                HIC"官道"NOR,
                HIC"官道"NOR,
                HIC"官道"NOR,
                HIC"南诏德化碑"NOR,
                HIC"太和城"NOR,
                HIC"大理城北"NOR,
                HIC"北门"NOR,
                HIC"牌坊"NOR,
                HIC"太和街口"NOR,
                HIC"中心广场"NOR,
                HIC"十字路口"NOR,
                HIC"大和街"NOR,
                HIC"兵营"NOR,
        });
        if( query_temp("marks/horserent", ob) != 1 && query("age", ob)>14 )
                return notify_fail("小孩子才可以免费坐马！你要交钱！\n");
        switch (random(3))
        {
                case 1:
                        hname=MAG"紫骝马"NOR;
                        break;
                case 2:
                        hname=RED"枣红马"NOR;
                        break;
                default:
                        hname=HIY"黄骠马"NOR;
                        break;
        }
        message_vision(
"马夫随手给$N牵来一匹"+hname+"。$N翻身跃上马背。动作潇洒利索。路边行人一阵
起哄: 喔噢喔噢。\n"NOR , ob );
        message_vision("\n只见$N骑两腿一夹，"+hname+"穿过客店而去。\n",ob);
        for (i = 0;i < sizeof(yz_dl);i ++)
                tell_object(ob,yz_dl[i] + "\n");
        ob->move("/d/dali/majiu");
        tell_room(environment(ob),query("name", ob)+"骑着"+hname+"一路顺利到达大理城。\n");
        message_vision("\n$N身形一转，跃下马来，姿态十分优美。闲人也给$N一大哄。\n",ob);
        delete_temp("marks/horserent", ob);
        return 1;
}