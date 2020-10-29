int do_rideyz()
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
        switch (random(4))
        {
                case 1:
                        hname=MAG"紫骝马"NOR;
                        break;
                case 2:
                        hname=RED"枣红马"NOR;
                        break;
                case 3:
                        hname=HIW"白骆驼"NOR;
                        break;
                default:
                        hname=HIY"黄骠马"NOR;
                        break;
        }
        message_vision(
"马夫随手给$N牵来一匹"+hname+"。$N翻身跃上"+hname+"背。动作潇洒利索。路边行人一阵
起哄: 喔噢喔噢。\n"NOR , ob );
        message_vision("\n只见$N两腿一夹，"+hname+"穿过军营而去。\n",ob);
        for ( i = sizeof(yz_dl) - 1;i >= 0;i--)
                tell_object(ob,yz_dl[i] + "\n");
        ob->move("/d/city/majiu");
        tell_room(environment(ob),query("name", ob)+"骑着"+hname+"一路顺利到达扬州城。\n");

        message_vision("\n$N身形一转，轻松落地，姿态十分优美。闲人也给$N一大哄。\n",ob);
        delete_temp("marks/horserent", ob);
        return 1;
}
