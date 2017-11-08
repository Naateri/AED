vector<Dist2Node<int> > distances; //Arreglo de distancias a que nodo
	bool seen[m_nodes.size()]; //Para saber si ya paso 
	Dist2Node<int> s;
	s.distance = -1; //-1 = infinite
	s.Node = 0;
	for (int i = 0; i < m_nodes.size(); i++){
		distances.push_back(s);
		seen[i] = 0;
	}
	distances[findInVector<Node*>(m_nodes, start)].distance = 0;
	distances[findInVector<Node*>(m_nodes, start)].Node = start;
	seen[findInVector<Node*>(m_nodes, start)] = 1;
	//Todo lo de arriba: Llenando los valores iniciales
	int mini = 0, index;
	Node* cur, *minDist;
	for(int i = 0; i < m_nodes.size() - 1; i++){
		mini = -1; //inicializa un nuevo minimo
		for(typename list<Edge*>::iterator it = cur->m_edges.begin(); it != cur->m_edges.end(); it++){ //recorrer aristas del nodo
			//pregunta si ya vio ese nodo ///REVISAR ESE OR
			if ( seen[findInVector<Node*>(m_nodes, (*it)->m_nodes[1])] || seen[findInVector<Node*>(m_nodes, (*it)->m_nodes[1])] ) continue;
			if (cur == (*it)->m_nodes[0]){  //guardamos las distancias
				if (distances[findInVector<Node*>(m_nodes, (*it)->m_nodes[1])].distance == -1){ //si nadie ha pasado por ahi
					distances[findInVector<Node*>(m_nodes, (*it)->m_nodes[1])].Node = (*it)->m_nodes[0];
					distances[findInVector<Node*>(m_nodes, (*it)->m_nodes[1])].distance = (*it)->m_data;
				} else {
					//distances[findInVector<Node*>(m_nodes, (*it)->m_nodes[0])].Node = (*it)->m_nodes[1];
					distances[findInVector<Node*>(m_nodes, (*it)->m_nodes[0])].distance 
						= min( (*it)->m_data, distance[findInVector<Node*>(m_nodes, cur)] );
				}
			if ( (*it)->m_data < mini || mini == -1) {
				mini = (*it)->m_data;
				minDist = *it;
			}
			}
		}
		seen[findInVector<Node*>(m_nodes, minDist)] = 1;
	}	
