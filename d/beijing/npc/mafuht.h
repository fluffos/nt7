int do_rideht()
{
        string hname;
        object ob = this_player();
        int i;
        string *bj_gw=({
                HIC"鸟市"NOR,
                HIC"西单"NOR,
                HIC"西单"NOR,
                HIC"西长安街"NOR,
                HIC"西长安广场"NOR,
                HIC"天安门广场"NOR,
                HIC"东长安广场"NOR,
                HIC"东长安街"NOR,
                HIC"王府井大街"NOR,
                HIC"王府井大街"NOR,
                HIC"王府井大街"NOR,
                HIC"朝阳道"NOR,
                HIC"朝阳道"NOR,
                HIC"朝阳门"NOR,
                HIC"大驿道"NOR,
                HIC"大驿道"NOR,
                HIC"大驿道"NOR,
                HIC"老龙头"NOR,
                HIC"山海关"NOR,
                HIC"官道"NOR,
                HIC"官道"NOR,
                HIC"官道"NOR,
                HIC"宁远"NOR,
                HIC"大道"NOR,
                HIC"大道"NOR,
                HIC"大道"NOR,
                HIC"大道"NOR,
                HIC"大道"NOR,
                HIC"木桥"NOR,
                HIC"南城"NOR,
                HIC"集市"NOR,
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
        for (i = 0; i < sizeof(bj_gw);i++)
                tell_object(ob,bj_gw[i] + "\n");
        ob->move("/d/guanwai/majiu");
        tell_room(environment(ob),query("name", ob)+"骑着"+hname+"一路顺利到达赫图阿拉。\n");
        message_vision("\n$N身形一转，跃下马来，姿态十分优美。闲人也给$N一大哄 !\n" ,ob);
        delete_temp("marks/horserent", ob);
        return 1;
}
