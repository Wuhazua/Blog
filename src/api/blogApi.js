export const fetchBlogPosts = async () => {
  
  return new Promise((resolve) => {
    setTimeout(() => {
      resolve([
        {
          id: 1,
          title: 'How to Build a React Portfolio',
          content: 'Content goes here...',
          date: '2025-04-01',
        },
        {
          id: 2,
          title: 'Understanding JavaScript Closures',
          content: 'Content goes here...',
          date: '2025-03-15',
        },
        
      ]);
    }, 1500); 
  });
};
