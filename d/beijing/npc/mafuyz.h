int do_rideyz()
{
        string hname;
        object ob = this_player();
        int i;
        string *bj_yz = ({
                HIC"鸟市"NOR,
                HIC"西单"NOR,
                HIC"西单"NOR,
                HIC"西长安街"NOR,
                HIC"西长安广场"NOR,
                HIC"天安门广场"NOR,
                HIC"长安街广场"NOR,
                HIC"凡陛桥"NOR,
                HIC"天坛北门"NOR,
                HIC"天坛"NOR,
                HIC"大道"NOR,
                HIC"永定门"NOR,
                HIC"大驿道"NOR,
                HIC"大驿道"NOR,
                HIC"大驿道"NOR,
                HIC"大驿道"NOR,
                HIC"大驿道"NOR,
                HIC"大驿道"NOR,
                HIC"小道"NOR,
                HIC"汝州城"NOR,
                HIC"大驿道"NOR,
                HIC"南阳城"NOR,
                HIC"汉水北岸"NOR,
                HIC"汉水南岸"NOR,
                HIC"大驿道"NOR,
                HIC"大驿道"NOR,
                HIC"北门"NOR,
                HIC"北大街"NOR,
                HIC"北大街"NOR,
                HIC"客店"NOR,
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
        for (i = 0; i < sizeof(bj_yz);i++)
                tell_object(ob,bj_yz[i] + "\n");
        ob->move("/d/city/majiu");
        tell_room(environment(ob),query("name", ob)+"骑着"+hname+"一路顺利到达扬州。\n");
        message_vision("\n$N身形一转，跃下马来，姿态十分优美。闲人也给$N一大哄 !\n" ,ob);
        delete_temp("marks/horserent", ob);
        return 1;
}
