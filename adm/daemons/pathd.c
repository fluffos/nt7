#define MAX 18

private string* find_path(object ob,object* rooms,string id);
void clean_path(object* rooms,string id);

mixed search_for_path(object ob, string name)
{
        object env,*temp,*temp1,*bak_room,*temp2,*new_temp;
        object room, _temp, _ob;
        string key,id;
        mapping exits;
        mixed n;
        int size, i;
        int a = 0;
        env = environment(ob);
        temp = ({env});
        temp1 = ({});
        exits=query("exits", env);
        bak_room = ({env});
        id = query("id", ob);
        
        // set_eval_limit(70000);
        while (a < MAX) 
        // We use Breadth_first search for Traversing graph.
        {
                reset_eval_cost();
                temp2 = copy(temp);
                temp = ({});
                
                foreach(room in temp2)
                {
                        exits=query("exits", room);
                        
                        if( !sizeof(exits) ) continue;
                        foreach(key in keys(exits))
                        {
                                _temp = get_object(exits[key]);
                                if( !objectp(_temp) ) continue;
                                                         
                                if( remove_ansi(query("short", _temp)) == name )
                                {
                                        set_temp("father-"+id, room, _temp);
                                        n = allocate(2);
                                        n[1] = allocate(sizeof(bak_room));
                                        n[0] = _temp;
                                        n[1] = find_path(n[0],bak_room,id);
                                        return n;
                                }
                                temp1 += ({ _temp });
                        }
                        size = sizeof(temp1);
                        for(i=0;i<size;i++)
                        {       
                                new_temp = copy(temp1[i]);
                                if ( sizeof(({new_temp}) & bak_room) ) {
                                        temp1[i] = 0;
                                } else
                                        set_temp("father-"+id, room, temp1[i]);
                        }
                        //temp1 = filter(temp1,(: $1 != 0 :));
                        temp1 -= ({0});
                        /*
                        foreach(_ob in temp1) 
                                set_temp("father-"+id, room, _ob);
                        */
                        bak_room += temp1;
                        temp += temp1;
                        temp1 = ({});
                } // end of foreach(temp2)
                a++;
        } // end of while
        return 1;
}

private string* find_path(object ob,object* rooms,string id)
{
        mapping exits;
        object *temp1;
        object temp = copy(ob);
        object _temp;
        string *temp2, key;
        int i;
        temp1 = ({});
        temp2 = ({});
        
        while(temp)
        {
                temp1 += ({temp});
                _temp = temp;
                temp = query_temp("father-"+id, temp);
                delete_temp("father-"+id, _temp);
        }
        
        clean_path(rooms, id);
        for( i = sizeof(temp1)-1;i>0;i-- )
        {
                if( i == 0 ) break;  
                exits = query("exits", temp1[i]);
                foreach(key in keys(exits))
                {
                        _temp = find_object(exits[key]);                     
                        if( !objectp(_temp) ) break;
                        if( _temp == temp1[i-1] )
                        {
                                temp2 += ({ key });
                                break;
                        }
                }
        }
        return temp2;
}       

void clean_path(object* rooms,string id)
{
        foreach(object room in rooms)
                delete_temp("father-"+id, room);
}
