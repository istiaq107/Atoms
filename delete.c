void deleteItem(struct grid *node){
  if (node) {
    deleteItem(node->next);
    free(node->next);
  }
}

void deleteList(struct root *list){
  deleteItem(list->first);
  free(list);
}

*->1->2->3->4->
