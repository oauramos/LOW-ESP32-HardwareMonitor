function findById(obj, id) {
  if (obj.id === id) {
    return obj
  }

  if (obj.Children) {
    for (let i = 0; i < obj.Children.length; i++) {
      const found = findById(obj.Children[i], id)
      if (found) {
        return found
      }
    }
  }

  return null
}

module.exports = { findById }
