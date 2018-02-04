/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasmith <hasmith@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 22:01:41 by hasmith           #+#    #+#             */
/*   Updated: 2018/02/03 23:28:57 by hasmith          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static void	go_thru_lnks(t_mast *mast)
{
	int i;
	t_links *tmp;

	i = 0;
	while (i < mast->rooms)
	{
		tmp = mast->hash_arr[i];
		while (tmp != 0)
		{
			printf(" (%s, %s)(%d, %d) |", tmp->l1, tmp->l2, tmp->l1_id, tmp->l2_id);
			//free(tmp);
			tmp = tmp->next;
		}
		printf("\n");
		i++;
	}
}

void DFS(t_mast *mast, int i)
{
	t_links *tmp;
	int j;
   
	
	if (!mast->found)
		printf("%s-",mast->r_arr_st[i]->room);
	if (i == mast->end)
		{mast->found = 1;return ;}
	// if (i == mast->start)
	//     printf("Start: ");
	// if (i == mast->end)
	//     {printf("End: ");return ;}
	tmp = mast->hash_arr[i];
	mast->r_arr_st[i]->visited = 1;
	while(tmp!=NULL)//
	{
		j = 0;
	   i=tmp->l2_id;

	   if(!mast->r_arr_st[i]->visited)
			DFS(mast, i);
		tmp=tmp->next;
	}
}







// void	path(t_mast *mast, int arr_size)
// {
// 	char **path;
// 	int i;

// 	i = mast->end;
// 	path = (char**)memalloc(sizeof(char*) * arr_size + 1);
// 	path[arr_size] = 0;
// 	arr_size--;
// 	while (arr_size >= 0)
// 	{
// 		path[arr_size] = mast->r_arr_st[i]->room;
// 		i = mast->r_arr_st[i]->prev;
// 		arr_size--;
// 	}
// 	i = 0;
// 	while (path[i])
// 		printf("%s-", path[i++]);
// 	printf("\n");
// }

void dkstra(t_mast *mast)
{
	t_links *tmp;
	int	qu[mast->rooms][3]; //0 is name of current, 1 is name of next, 2 is weight
	int last;
	int weight;
	int cnt;

	weight = 0;
	last = 0;
	cnt = 0;
	qu[last][0] = mast->start;
	mast->r_arr_st[qu[cnt][0]]->weight = weight;
	while (qu[weight][0] != mast->end)
	{
			printf("%s\n", mast->r_arr_st[qu[weight][0]]->room);
		tmp = mast->hash_arr[qu[weight][0]];
		(cnt == 0) ? cnt++ : 0;
		weight++;
		while(tmp != NULL)//
		{
			int cnt1 = 0;
			for (int i = 0; i <= cnt; i++)
			{
				if (qu[i][0] == tmp->l2_id && qu[i][2] != 0 && qu[i][2] < weight)
					cnt1++;
			}
			if (cnt1 == 0)
			{
				
				qu[cnt][0] = tmp->l2_id;
				qu[cnt][1] = tmp->l1_id;
				qu[cnt][2] = weight;
				printf("%s-%s;wieght:%d\n", mast->r_arr_st[qu[cnt][0]]->room, mast->r_arr_st[qu[cnt][1]]->room, weight);
				cnt++;
				if (qu[cnt][0] == mast->end)
					break ;
			}

			//mast->r_arr_st[qu[cnt][0]]->weight = weight;
			//if(!mast->r_arr_st[i]->visited)

			tmp = tmp->next;
			
		}
		if (qu[weight][0] == mast->end || qu[cnt][0] == mast->end)
			break ;
	}
	while (1)
	{
		printf("%s-", mast->r_arr_st[qu[weight][0]]->room);
		if (qu[weight][0] == mast->start)
			break ;
		for (int i = 0; i <= cnt; i++)
		{
			if (qu[i][0] == qu[weight][1])
			{
				weight = i;
				break ;
			}
		}
	}
	//pass the size nd the mast
}




int     solve(t_mast *mast)
{

	printf("\n", mast->start);
	dkstra(mast);
	//DFS(mast, mast->start);
	printf("\n");

	
	// int i;
	// t_links *tmp;

	// i = 0;
	// while (/*list is not empty*/)
	// {
	// 	tmp = mast->hash_arr[i];
	// 	while (tmp != 0)
	// 	{
	// 		//printf(" (%s, %s)(%d, %d) |", tmp->l1, tmp->l2, tmp->l1_id, tmp->l2_id);
	// 		//free(tmp);
	// 		tmp = tmp->next;
	// 	}
	// 	printf("\n");
	// 	i++;
	// }
	return (0);
}





// int Astar(t_mast *mast)//start, goal)
// 	// The set of nodes already evaluated
// 	t_room *closedSet;// := {}

// 	// The set of currently discovered nodes that are not evaluated yet.
// 	// Initially, only the start node is known.
// 	t_room *openSet;// := {start}
// 	openSet = mast->r_arr_st[mast->start];

// 	// For each node, which node it can most efficiently be reached from.
// 	// If a node can be reached from many nodes, cameFrom will eventually contain the
// 	// most efficient previous step.
// 	t_room *cameFrom;// := an empty map

// 	// For each node, the cost of getting from the start node to that node.
// 	t_room *weight;// := map with default value of Infinity

// 	// The cost of going from start to start is zero.
// 	weight[start] == 0

// 	// For each node, the total cost of getting from the start node to the goal
// 	// by passing by that node. That value is partly known, partly heuristic.
// 	t_room *fweight;// := map with default value of Infinity

// 	// For the first node, that value is completely heuristic.
// 	fweight[start] := heuristic_cost_estimate(start, goal)

// 	while openSet is not empty
// 		current := the node in openSet having the lowest fweight[] value
// 		if current = goal
// 			return reconstruct_path(cameFrom, current)

// 		openSet.Remove(current)
// 		closedSet.Add(current)

// 		for each neighbor of current
// 			if neighbor in closedSet
// 				continue		// Ignore the neighbor which is already evaluated.

// 			if neighbor not in openSet	// Discover a new node
// 				openSet.Add(neighbor)
			
// 			// The distance from start to a neighbor
// 			//the "dist_between" function may vary as per the solution requirements.
// 			tentative_weight := weight[current] + dist_between(current, neighbor)
// 			if tentative_weight >= weight[neighbor]
// 				continue		// This is not a better path.

// 			// This path is the best until now. Record it!
// 			cameFrom[neighbor] := current
// 			weight[neighbor] := tentative_weight
// 			fweight[neighbor] := weight[neighbor] + heuristic_cost_estimate(neighbor, goal) 

// 	return failure

// function reconstruct_path(cameFrom, current)
// 	total_path := [current]
// 	while current in cameFrom.Keys:
// 		current := cameFrom[current]
// 		total_path.append(current)
// 	return total_path

	