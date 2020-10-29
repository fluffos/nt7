void destroying(object me)
{
        destruct(me);
        return;
}

void init()
{
        object ob;

        ::init();

        ob = this_player();
        add_action("do_kill", "kill");
        add_action("do_kill", "hit");
}

int checking(object me, object ob)
{
        if( query("qi", me)<1 )
        {
                  message_vision("\n$N扑在地上挣扎了几下，口中喷出几口"HIR"鲜血"NOR"，死了！\n"NOR,me);
                  if( query_temp("start_job", ob) == 1 )
                  {
                          addn_temp("killed_mgb", 1, ob);
                  }
                  else
                          addn_temp("help_killed", 1, ob);
                  call_out("destroying",1,me);                  
                  if(ob->query_condition("jobshadi_limit")==0)
                  {
                          message_vision(CYN"\n一个守城宋兵跑过来说道：蒙古靼子暂时被击退了，$N可以回去复命了！\n"NOR,ob);
                          set_temp("job_over", 1, ob);
                          delete_temp("start_job", ob);
                  }
                  else
                  {
                call_out("clone_rob",1,ob);
        message_vision("\n test!\n"NOR,ob);
                               return 1;
                  }
        }

        if (me->is_fighting()) 
        {
                call_out("checking",1, me, ob);
                return 1;
        }

        return 1;
}

int do_kill(string arg)
{
        object who = this_player();
        object me = this_object();
        if (me->is_fighting()) 
        {
                message_vision(CYN"\n加油！加油！\n"NOR,who);
                return 1;
        }
        if(!arg || present(arg,environment(me))!=me) return 0;
        me->kill_ob(who);
        call_out("checking",1,me,who);
        return 1;
} 

void clone_rob(object ob)
{
        object room;
        object robber;
       message_vision("\n test!!!!!\n"NOR,this_player());
          room = environment(this_player());
        switch( random(2) ) {
                case 0:
                        message_vision(HIR"城下又爬上来一个蒙古兵士。\n" NOR,this_player()); 
           robber=new(__DIR__"robber1");
                        robber->move(room);
                        robber->kill_ob(this_player());
                        robber->checking(robber,this_player());
                        break;
                case 1:
                        message_vision(HIR"城下又爬上来一个蒙古将领。\n" NOR,this_player()); 
           robber=new(__DIR__"robber2");
                        robber->move(room);
                        robber->kill_ob(this_player());
                        robber->checking(robber,this_player());
                        break;
        }
        return;
}