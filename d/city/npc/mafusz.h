int do_ridesz()
{
        string hname;
        object ob = this_player();
        int i;
        string *yz_sz = ({
                HIC"客店"NOR,
                HIC"北大街"NOR,
                HIC"中央广场"NOR,
                HIC"东大街"NOR,
                HIC"东大街"NOR,
                HIC"东门"NOR,
                HIC"大驿道"NOR,
                HIC"大驿道"NOR,
                HIC"山路"NOR,
                HIC"山路"NOR,
                HIC"东门"NOR,
                HIC"东大街"NOR,
                HIC"东大街"NOR,
                HIC"沧浪亭"NOR,
                HIC"北大街"NOR,
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
        for ( i = 0;i < sizeof(yz_sz);i ++)
                tell_object(ob,yz_sz[i] + "\n");
        ob->move("/d/suzhou/majiu");
        tell_room(environment(ob),query("name", ob)+"骑着"+hname+"一路顺利到达苏州。\n");
        message_vision("\n$N身形一转，跃下马来，姿态十分优美。闲人也给$N一大哄 !\n" ,ob);
        delete_temp("marks/horserent", ob);
        return 1;
}